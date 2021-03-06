#include "feature_op/S_direct.h"

#include <cstdlib>

#include "util/bisheng_string_tool.h"

XFEA_BISHENG_NAMESPACE_GUARD_BEGIN

// 注册该特征类
// TODO 在此处注册不生效，在util/bisheng_factory.cpp中注册可以
// XFEA_BISHNEG_USING_FEATURE(S_direct);

// 初始化及参数检查, 需要依赖的字段个数必须为1
ReturnCode S_direct::init(const ExtractorConfig& extractor_config) {
    // 依赖的字段个数必须为1
    if (_depend_col_index_vec.size() != 1) {
        XFEA_BISHENG_FATAL_LOG("depend field number must be equal to 1 in feature [%s]!", _name.c_str());
        return RC_ERROR;
    }

    XFEA_BISHENG_NOTICE_LOG("_output_ratio of feature [%s] is [%f]!", _name.c_str(), _output_ratio);
    return RC_SUCCESS;
}

// 根据单个字段的内容直接生产特征
ReturnCode S_direct::generate_fea(const LogRecordInterface& record, FeaResultSet& fea_result_set, bool copy_value) {
    // 获取抽取特征依赖的字段的index
    // 使用at有抛出异常的风险（init函数要做好_depend_col_index_vec size检查）
    int depend_col_field_index = _depend_col_index_vec.at(0);

    if (!record.is_update(depend_col_field_index))
        return RC_SUCCESS;

    // 获取其对应的字段值
    const char* fea_text = record.get_value(depend_col_field_index);
    if (NULL == fea_text) {
        XFEA_BISHENG_WARN_LOG("get index[%d] value of record failed in feature [%s]!", depend_col_field_index, _name.c_str());
        return RC_WARNING;
    }
    // 计算特征签名及将抽取的特征放入fea_result_set，emit_feature位于SingleSlotFeatureOp
    return SingleSlotFeatureOp::emit_feature(_name, 0, fea_text, fea_result_set, copy_value);
}

XFEA_BISHENG_NAMESPACE_GUARD_END

