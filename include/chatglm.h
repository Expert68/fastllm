//
// Created by huangyuyang on 5/11/23.
//

#ifndef FASTLLM_CHATGLM_H
#define FASTLLM_CHATGLM_H

#include "basellm.h"
#include "cmath"

#include <iostream>

namespace fastllm {
    class ChatGLMModel: public basellm {
	public:
        ChatGLMModel (); // 构造函数

		virtual void LoadFromFile(const std::string &fileName); // 从文件读取

        // 推理
		virtual int Forward(
                const Data &inputIds,
                const Data &attentionMask,
                const Data &positionIds,
                std::vector <std::pair <Data, Data> > &pastKeyValues);

        std::vector <int> ForwardBatch(
                int batch,
                const Data &inputIds,
                const Data &attentionMask,
                const Data &positionIds,
                std::vector <std::pair <Data, Data> > &pastKeyValues);

		virtual std::string Response(const std::string& input, RuntimeResult retCb); // 根据给出的内容回复

        virtual void ResponseBatch(const std::vector <std::string> &inputs,
                                   std::vector <std::string> &outputs,
                                   RuntimeResultBatch retCb);

		virtual void SaveLowBitModel(const std::string &fileName, int bit); // 存储成量化模型

		virtual void WarmUp(); // 预热
    private:
		virtual void RotatePosition2D(Data &data, const Data &positionIds); // 二维位置编码

		virtual void CausalMask(Data &data, int start) {}; // 因果mask？
    };
}

#endif //FASTLLM_CHATGLM_H
