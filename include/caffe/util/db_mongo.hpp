//#ifdef USE_MONGO
#ifndef CAFFE_UTIL_DB_MONGO_HPP
#define CAFFE_UTIL_DB_MONGO_HPP

#include <string>
#include <vector>
#include <map>

#include "mongoc.h"
#include <stdio.h>
#include <stdlib.h>

#include "caffe/util/db.hpp"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "caffe/util/io.hpp"

namespace caffe { namespace db {

class MongoDBCursor : public Cursor {
 public:
  explicit MongoDBCursor(mongoc_cursor_t* cursor, std::string label_field, std::string image_field, std::map<std::string, int> label_map,
  int new_width, int new_height, int channels)
    : cursor_(cursor), valid_(false), label_field_(label_field), image_field_(image_field), 
      label_map_(label_map), new_width_(new_width), new_height_(new_height), channels_(channels) {
    SeekToFirst();
  }
  virtual ~MongoDBCursor() {
      mongoc_cursor_destroy(cursor_);
  }
  virtual void SeekToFirst() { Seek(); }
  virtual void Next() { Seek(); }

  virtual string key() {
    string key = bson_as_json (doc_, NULL);
    return key;
  }

  virtual string value() {
    bson_iter_t iter;
    int label_index = -1;
    LOG(INFO) << "start label";
    if (bson_iter_init (&iter, doc_) &&
      bson_iter_find (&iter, label_field_.c_str())) {
      const bson_value_t *label_value = bson_iter_value(&iter);
      string label = string(label_value->value.v_utf8.str);
      if (label_map_.find(label) != label_map_.end()) {
        label_index = label_map_[label];
      }
      LOG(INFO) << "label is " << label << "label index " << label_index;
    }
    if (label_index == -1) {
      Next();
      return string("");
    }

    Datum datum;
    if (bson_iter_init (&iter, doc_) &&
      bson_iter_find (&iter, image_field_.c_str())) {
      LOG(INFO) << "key is " << bson_iter_key(&iter);
      const bson_value_t *value = bson_iter_value(&iter);
      //LOG(INFO) << "value is " << bson_iter_value (&iter)->value.v_binary.data;
      cv::Mat image = cv::imdecode(cv::Mat(1, value->value.v_binary.data_len, CV_8UC1, value->value.v_binary.data), cv::IMREAD_COLOR);
      //cv::imwrite("b.jpg", image);
      if (image.channels() == 1 && channels_ == 3) {
        cv::cvtColor(image, image, CV_GRAY2BGR);
      } else if (image.channels() == 3 && channels_ == 1) {
        cv::cvtColor(image, image, CV_BGR2GRAY);
      }
      cv::resize(image, image, cv::Size(new_width_, new_height_));
      CVMatToDatum(image, &datum);
    }

    datum.set_label(label_index);  
    string out;
    datum.SerializeToString(&out);
    return out;
  }
  virtual bool valid() { return valid_; }

 private:
  void Seek() {
      bson_error_t error;
      if (mongoc_cursor_error(cursor_, &error)) {
        
      } else {
        mongoc_cursor_next(cursor_, &doc_);
      }
  }


  const bson_t *doc_;
  mongoc_cursor_t *cursor_;
  bool valid_;
  std::string label_field_;
  std::string image_field_;
  std::map<std::string, int> label_map_;
  int new_width_;
  int new_height_;
  int channels_;
};

class MongoDBTransaction : public Transaction {
 public:
  explicit MongoDBTransaction(){ }
  virtual void Put(const string& key, const string& value) {}
  virtual void Commit() {}

 private:

  DISABLE_COPY_AND_ASSIGN(MongoDBTransaction);
};

class MongoDB : public DB {
 public:
  MongoDB() : client_(NULL), collection_(NULL), cursor_(NULL) {   
    LOG(INFO) << "Mongo DB \n"; 
    mongoc_init(); 
  }
  virtual ~MongoDB() { Close(); }
  virtual void Open(const string& source, Mode mode);
  virtual void Close() {
    mongoc_cursor_destroy(cursor_);
    mongoc_collection_destroy(collection_);
    mongoc_client_destroy(client_);
    mongoc_cleanup();
  }
  virtual MongoDBCursor* NewCursor();
  virtual MongoDBTransaction* NewTransaction();
  virtual void set_data_param(const caffe::DataParameter &data_param);

 private:
    mongoc_client_t *client_;
    mongoc_collection_t *collection_;
    mongoc_cursor_t *cursor_;
    bson_t query_;

    std::string db_name_;
    std::string collection_name_;
    std::string label_field_;
    std::string image_field_;
    std::map<std::string, int> label_map_;
    std::string label_txt_;
    int new_height_;
    int new_width_;
    int channels_;

    void SetLabelTxt(std::string label_txt);
};

}  // namespace db
}  // namespace caffe

#endif  // CAFFE_UTIL_DB_MONGO_HPP
//#endif  // USE_MONGO
