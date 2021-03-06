/*
 * poolLayer.h
 *
 *  Created on: Nov 28, 2015
 *      Author: tdx
 */

#ifndef POOLLAYER_H_
#define POOLLAYER_H_

#include<tuple>
#include<string>
#include<cudnn.h>
#include<math.h>
#include"layersBase.h"
#include"../common/utility.cuh"
#include"../config/config.h"
#include"../cuDNN_netWork.h"
#include"../tests/test_layer.h"

using namespace std;


class poolLayer : public layersBase
{
public:
	typedef tuple<string, int, int, int, int, int, int, int> param_tuple;
	poolLayer(string name);
	poolLayer(string name, const param_tuple& agrs);
	poolLayer(poolLayer* layer);
	void forwardPropagation(string train_or_test);
	void backwardPropagation(float Momentum);
	void saveWeight(FILE*file){}
	void readWeight(FILE*file){}
	~poolLayer()
	{
		MemoryMonitor::instanceObject()->freeGpuMemory(dstData);
		MemoryMonitor::instanceObject()->freeGpuMemory(diffData);
		destroyHandles();
		delete m_poolMethod;
	}

	void createHandles();
	void destroyHandles();

	int getOutputSize()
	{
		return outputSize;
	}

private:
	cudnnPoolingMode_t PoolingMode;
	ConfigPoolMethod* m_poolMethod;
	string pool_Type;
	int poolDim;
	int pad_h;
	int pad_w;
	int stride_h;
	int stride_w;
	int outputSize;
	int prev_num;
	int prev_channels;
	int prev_height;
	int prev_width;

private:
	cudnnTensorDescriptor_t srcTensorDesc = NULL;
	cudnnTensorDescriptor_t dstTensorDesc = NULL;
	cudnnPoolingDescriptor_t poolingDesc = NULL;
	cudnnTensorDescriptor_t srcDiffTensorDesc = NULL;
	cudnnTensorDescriptor_t dstDiffTensorDesc = NULL;
};



#endif /* POOLLAYER_H_ */
