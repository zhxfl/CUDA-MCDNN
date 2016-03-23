/*
 * layersBase.h
 *
 *  Created on: Nov 23, 2015
 *      Author: tdx
 */

#ifndef LAYERSBASE_H_
#define LAYERSBASE_H_

#include"../common/cuMatrix.h"
#include<string>
#include<map>
#include<vector>
#include"math.h"
using namespace std;

class layersBase
{
public:
	virtual void forwardPropagation(string train_or_test) = 0;
	virtual void backwardPropagation(float Momentum) = 0;
	virtual int getOutputSize() = 0;
	virtual void saveWeight(FILE*file) = 0;
	virtual void readWeight(FILE*file) = 0;
    void setBranchIndex(int nIndex){ 
        m_nCurBranchIndex = nIndex;
    }
	void adjust_learnRate(int index, double lr_gamma, double lr_power)
	{
		lrate = static_cast<float>(lrate * pow((1.0 + lr_gamma * index), (-lr_power)));
	}
public:
    void insertPrevLayer(layersBase* layer){
        prevLayer.push_back(layer);
    }
    void insertNextlayer(layersBase* layer){
        nextLayer.push_back(layer);
    }

public:
	string _name;
	string _inputName;
	int number;
	int channels;
	int height;
	int width;
	int inputImageDim;
	int inputAmount;
	float lrate;
	float *diffData;
	float *srcData , *dstData;
    int m_nCurBranchIndex;
    vector<layersBase*>prevLayer;
    vector<layersBase*>nextLayer;
};

class Layers
{
public:

	static Layers* instanceObject()
	{
	  static Layers* layers = new Layers();
	  return layers;
	}

	/*get layer by name*/
	layersBase * getLayer(string name);

	/*store the layers by name*/
	void storLayers(string name, layersBase* layer);
	/*store the layers name*/
	void storLayersName(string);
	/*get layers name by index*/
	string getLayersName(int index);

	/*get layer num*/
	int getLayersNum()
	{
		return _layersMaps.size();
	}

private:
	map<string,layersBase*> _layersMaps;
	vector<string> _layersName;
};


#endif /* LAYERSBASE_H_ */
