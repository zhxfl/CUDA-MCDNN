/*
 * Concat.h
 *
 *  Created on: Mar 6, 2016
 *      Author: tdx
 */

#ifndef CONCAT_H_
#define CONCAT_H_

#include"../layers/layersBase.h"
#include"../common/MemoryMonitor.h"
#include"../common/checkError.h"
#include"../common/utility.cuh"
#include"../common/cuBaseVector.h"
#include"../cuDNN_netWork.h"
#include"../tests/test_layer.h"
#include<tuple>

class Concat
{
public:
	typedef tuple<int, int, int, int>param_tuple;
	Concat(Layers*& Inner_Layers, const param_tuple& args);
	void concatInit();
	float* forwardSetup();
	float* backwardSetup();
	void split_DiffData(int index, float* diffData);

	~Concat()
	{
		MemoryMonitor::instanceObject()->freeCpuMemory(host_offset);
		MemoryMonitor::instanceObject()->freeCpuMemory(host_channels);
		MemoryMonitor::instanceObject()->freeCpuMemory(separateDim);
		MemoryMonitor::instanceObject()->freeGpuMemory(dstData);
		MemoryMonitor::instanceObject()->freeGpuMemory(diffData);
		MemoryMonitor::instanceObject()->freeGpuMemory(dev_offset);
		MemoryMonitor::instanceObject()->freeGpuMemory(dev_channels);
		MemoryMonitor::instanceObject()->freeGpuMemory(separate_diffData);
		prevDiff.vector_clear();
		separate_dstData.vector_clear();
	}

private:
	int number;
	int channels;
    int height;
    int width;
    int size;
    int one;
    int three;
    int five;
    int pool_proj;
    int prev_num;
    int prev_channels;
    int prev_height;
    int prev_width;
    int* separateDim;
    int* host_offset;
    int* dev_offset;
    int* dev_channels;
    int* host_channels;
    float* separate_diffData;
	float* dstData;
	float* diffData;
	Layers *InnerLayers;
	cuBaseVector<float> separate_dstData;
	cuBaseVector<float> prevDiff;

};



#endif /* CONCAT_H_ */
