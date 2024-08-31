#ifndef _l_fann_h_
#define _l_fann_h_

#include "winlite.h"

#include <fann.h>
#pragma comment(lib, "fannfloat.lib")

#define UINT2PANN(u) ((struct fann *)u)
#define PANN2UINT(pa) ((UINT)pa)

#define UINT2PTRN(u) ((struct fann_train_data *)u)
#define PTRN2UINT(pa) ((UINT)pa)

void l_fann_register(lua_State *l);
void l_fann_globals(lua_State *l);

LUA_FUNC(annCreate);
LUA_FUNC(annCreateFromFile);
LUA_FUNC(annRun);
LUA_FUNC(annSaveToFile);
LUA_FUNC(annDestroy);

LUA_FUNC(annActivationSteepnessLayer);
LUA_FUNC(annActivationFunctionLayer);
LUA_FUNC(annTrainStopFunction);
LUA_FUNC(annBitFailLimit);
LUA_FUNC(annTrainAlgorithm);
LUA_FUNC(annRandomizeWeights);
LUA_FUNC(annLearnRate);

LUA_FUNC(annTrain);
LUA_FUNC(annTrainOnData);
LUA_FUNC(annTrainOnFile);
LUA_FUNC(annTrainEpoch);

LUA_FUNC(anntdCreate);
LUA_FUNC(anntdCreateFromFile);
LUA_FUNC(anntdShuffle);
LUA_FUNC(anntdScaleInput);
LUA_FUNC(anntdScaleOutput);
LUA_FUNC(anntdScale);
LUA_FUNC(anntdMerge);
LUA_FUNC(anntdDuplicate);
LUA_FUNC(anntdSubset);
LUA_FUNC(anntdLength);
LUA_FUNC(anntdNumInput);
LUA_FUNC(anntdNumOutput);
LUA_FUNC(anntdSaveToFile);
LUA_FUNC(anntdDestroy);

#endif
