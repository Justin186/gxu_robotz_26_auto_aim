#include "openvinoInfer.hpp"

#define BLUE 0
#define RED  1
#define NONE_ 2
#define CURR true
#define NEXT false

OpenvinoInfer::OpenvinoInfer(const std::string &config_path) {
    auto yaml_ = tools::load(config_path);
    auto xml_path = tools::read<std::string>(yaml_, "xml_path");
    auto bin_path = tools::read<std::string>(yaml_, "bin_path");
    this->model_ = this->core_.read_model(xml_path, bin_path);

    this->score_threshold = tools::read<float>(yaml_, "score_threshold");
    this->nms_threshold = tools::read<float>(yaml_, "nms_threshold");

    ov::preprocess::PrePostProcessor ppp = ov::preprocess::PrePostProcessor(this->model_);

    ppp.
            input().
            tensor().
            set_element_type(ov::element::u8).
            set_layout("NHWC").
            set_color_format(ov::preprocess::ColorFormat::BGR);

    ppp.
            input().
            preprocess().
            convert_element_type(ov::element::f32).
            convert_color(ov::preprocess::ColorFormat::RGB).
            scale({255.f, 255.f, 255.f});

    ppp.
            input().
            model().
            set_layout("NCHW");

    ppp.
            output(0).
            tensor().
            set_element_type(ov::element::f32);

    ppp.
            output(1).
            tensor().
            set_element_type(ov::element::f32);

    ppp.
            output(2).
            tensor().
            set_element_type(ov::element::f32);


    this->model_ = ppp.build();

    auto device = tools::read<std::string>(yaml_, "device");
    this->compiled_model_ = this->core_.compile_model(this->model_, device);
    this->compiled_model_next_ = this->core_.compile_model(this->model_, device);

    this->infer_requests_.insert(std::pair<bool, ov::InferRequest>(CURR, this->compiled_model_.create_infer_request()));
    this->infer_requests_.insert(std::pair<bool, ov::InferRequest>(NEXT, this->compiled_model_next_.create_infer_request()));
}

std::vector<OpenvinoInfer::Light> OpenvinoInfer::infer(cv::Mat &src, const cv::Size2d &dst_size, const int &my_color, const bool &startup) {
    ov::Shape inputShape = this->compiled_model_.input().get_shape();
    int model_h = inputShape[1];
    int model_w = inputShape[2];

    // We direct resize to the MODEL'S exact input shape to avoid gray padding 
    // and avoid out-of-bounds or truncation.
    cv::resize(src, this->canvas_next_, cv::Size(model_w, model_h), 0, 0, cv::INTER_CUBIC);

    auto *input_data = (uint8_t *)this->canvas_next_.data;

    ov::Tensor input_tensor = ov::Tensor(
            this->compiled_model_.input().get_element_type(),
            this->compiled_model_.input().get_shape(),
            input_data);

    if (startup) {
        this->canvas_curr_ = this->canvas_next_.clone();
        this->infer_requests_[CURR].set_input_tensor(input_tensor);
        this->infer_requests_[CURR].start_async();
        cv::swap(this->canvas_curr_, this->canvas_next_);
        return {};
    }

    this->infer_requests_[NEXT].set_input_tensor(input_tensor);
    this->infer_requests_[NEXT].start_async();
    this->infer_requests_[CURR].wait();

//    std::vector<int> _class_ids;
    std::vector<float> confidences;
//    std::vector<double> _sizes;
    std::vector<cv::Rect> boxes;
    std::vector<OpenvinoInfer::Light> Lights;
    std::vector<int> nms_result;
    const ov::Tensor &outputTensor = this->infer_requests_[CURR].get_output_tensor(0);
    ov::Shape outputShape = outputTensor.get_shape();

    auto *outputData = outputTensor.data<float>();
    
    for(size_t i = 0 ; i < outputShape[1] ; ++i){
        float* detection = &outputData[i * outputShape[2]];
        //normalize the coordinate
        float confidence = detection[4];
        if(confidence >= this->score_threshold){
            float* classesConfidence = &detection[4 + 1];
            float* colorsConfidence = &detection[4 + 1 + 9];
            cv::Mat scores(1, 9, CV_32FC1, classesConfidence);
            cv::Mat colors(1, 4, CV_32FC1, colorsConfidence);
            cv::Point classIdPoint;
            double maxClassConfidence;
            cv::minMaxLoc(scores, nullptr, &maxClassConfidence, nullptr, &classIdPoint);

            if(maxClassConfidence >= this->score_threshold){

                if (classIdPoint.x != 8) {
                    continue;
                }
                
                // Map coordinates from Model target size back to requested dst_size
                float scale_x = dst_size.width / (float)model_w;
                float scale_y = dst_size.height / (float)model_h;
                
                float cx = detection[0] * scale_x;
                float cy = detection[1] * scale_y;
                float w = detection[2] * scale_x;
                float h = detection[3] * scale_y;
                
                OpenvinoInfer::Light Light;

                Light.id = classIdPoint.x;
                Light.score = confidence;
                Light.center_point = cv::Point2f(cx, cy);
                Light.box = cv::Rect2d(cx - w / 2., cy - h / 2., w, h);
                Lights.emplace_back(Light);

                confidences.emplace_back(confidence);
                boxes.emplace_back(cv::Rect(cx - w / 2., cy - h / 2., w, h));
               
            }
        }
    }

    cv::dnn::NMSBoxes(
            boxes,
            confidences,
            this->score_threshold,
            this->nms_threshold, nms_result);
    std::vector<OpenvinoInfer::Light> result;
    for(const int &idx : nms_result){
        result.emplace_back(OpenvinoInfer::Light {
                Lights[idx].id,
                Lights[idx].score,
                Lights[idx].box,
                Lights[idx].center_point
        });
    }

    auto change = this->infer_requests_[CURR];
    this->infer_requests_[CURR] = this->infer_requests_[NEXT];
    this->infer_requests_[NEXT] = change;
    
    cv::swap(this->canvas_curr_, this->canvas_next_);
    
    return result;
}

OpenvinoInfer::Resize OpenvinoInfer::letterBox(cv::Mat &src, const cv::Size2d &dst_size) {
    int w = src.cols;
    int h = src.rows;

    double r_w = (double)dst_size.width / w;
    double r_h = (double)dst_size.height / h;
    double r = std::min(r_w, r_h);

    int new_w = (int)(w * r);
    int new_h = (int)(h * r);

    cv::Mat resized_image;

    cv::resize(src, resized_image, cv::Size(new_w, new_h), cv::INTER_CUBIC);

    cv::Mat canvas(dst_size, CV_8UC3, cv::Scalar(128, 128, 128));

    int dx = (int)((dst_size.width - new_w) / 2.);
    int dy  =(int)((dst_size.height - new_h) / 2.);

    resized_image.copyTo(canvas(cv::Rect(dx, dy, new_w, new_h)));
//     cv::imshow("resized_image", canvas);
//     cv::waitKey(1);
    return {canvas, dx, dy};
}

void OpenvinoInfer::fitRec(std::vector<OpenvinoInfer::Light> &bboxes, cv::Size2d ori_size, cv::Size2d now_size) {
    double scale = std::max((double)ori_size.width / now_size.width, (double)ori_size.height / now_size.height);

    for (auto &bbox : bboxes) {
        bbox.box.x = (bbox.box.x - now_size.width / 2) * scale + ori_size.width / 2;
        bbox.box.y = (bbox.box.y - now_size.height / 2) * scale + ori_size.height / 2;
        bbox.box.width *= scale;
        bbox.box.height *= scale;
        bbox.center_point.x = (bbox.center_point.x - now_size.width / 2) * scale + ori_size.width / 2;
        bbox.center_point.y = (bbox.center_point.y - now_size.height / 2) * scale + ori_size.height / 2;
    }
}