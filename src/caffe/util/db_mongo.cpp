//#ifdef USE_MONGO
#include "caffe/util/db_mongo.hpp"
#include <sys/stat.h>
#include <bson.h>
#include <string>

namespace caffe { namespace db {

void MongoDB::Open(const string& source, Mode mode) {

  client_ = mongoc_client_new(source.c_str());
  if (!client_) {
      LOG(FATAL) << "open mongodb failed " << source;
      return;
  }
  LOG(INFO) << "Opened mongodb " << source;
}

void MongoDB::set_data_param(const caffe::DataParameter &data_param) {
  label_txt_ = data_param.label_txt();
  new_width_ = data_param.new_width();
  new_height_ = data_param.new_height();
  channels_ = data_param.channels();
  label_field_ = data_param.label_field();
  image_field_ = data_param.image_field();
  db_name_ = data_param.db_name();
  collection_name_ = data_param.collection_name();
  SetLabelTxt(label_txt_);
}

void MongoDB::SetLabelTxt(std::string label_txt) {
  std::ifstream label_txt_file(label_txt);
  std::string line;
  int label_index = 0;
  while (std::getline(label_txt_file, line)) {
    int pos = line.find_last_of(' ');
    string label = line.substr(0, pos);
    //string label = line.substr(line.length() - 1);
    LOG(INFO) << "label map key: " << label << ", value " << label_index; 
    label_map_.insert(std::map<std::string, int>::value_type(label, label_index++));
  }
}

MongoDBCursor* MongoDB::NewCursor() {
  mongoc_client_set_error_api(client_, 2);
  bson_t query;
  bson_init(&query);
  collection_ = mongoc_client_get_collection(client_, db_name_.c_str(), collection_name_.c_str());
  cursor_ = mongoc_collection_find(collection_, MONGOC_QUERY_NONE, 0, 0, 0, 
                            &query, NULL, NULL);
  LOG(INFO) << "new cursor";
  //bson_destroy (query);
  return new MongoDBCursor(cursor_, label_field_, image_field_, label_map_,
    new_width_, new_height_, channels_);
}

MongoDBTransaction* MongoDB::NewTransaction() {
  return new MongoDBTransaction();
}


}  // namespace db
}  // namespace caffe
//#endif  // USE_MONGO
