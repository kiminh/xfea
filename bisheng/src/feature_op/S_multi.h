#ifndef XFEA_BISHENG_FEATURE_OP_S_DIRECT_MULTI_H_
#define XFEA_BISHENG_FEATURE_OP_S_DIRECT_MULTI_H_

#include "feature_op/single_slot_feature_op.h"

XFEA_BISHENG_NAMESPACE_GUARD_BEGIN

// 拼接多个字段的内容直接生产特征
class S_multi : public SingleSlotFeatureOp {
public:
    const static int kBufSize = 2048;
    const static char kDefaultSeperator = '_';

public:
    S_multi(): _seperator(kDefaultSeperator) {
        _buf[0] = '\0';
    }

    // 初始化及参数检查, 需要依赖的字段个数必须为1
    virtual ReturnCode init(const ExtractorConfig& extractor_config);

    // 根据单个字段的内容直接生产特征
    virtual ReturnCode generate_fea(const LogRecordInterface& record, FeaResultSet& fea_result_set);

    // 资源回收
    virtual void finalize() {
        // Nothing to do
    }

private:
    char _seperator;
    char _buf[kBufSize];
};

XFEA_BISHENG_NAMESPACE_GUARD_END

#endif
