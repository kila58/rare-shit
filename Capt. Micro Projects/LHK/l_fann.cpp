#include "l_fann.h"

void l_fann_register(lua_State *l)
{
	LUA_REG(l, annCreate);
	LUA_REG(l, annCreateFromFile);
	LUA_REG(l, annDestroy);
	LUA_REG(l, annSaveToFile);
	LUA_REG(l, annRandomizeWeights);
	LUA_REG(l, annLearnRate);
	LUA_REG(l, annTrainAlgorithm);
	LUA_REG(l, annTrainOnFile);
	LUA_REG(l, annRun);
}

void l_fann_globals(lua_State *l)
{
	lua_pushinteger(l, FANN_TRAIN_INCREMENTAL);
	lua_setglobal(l, "FANN_TRAIN_INCREMENTAL");
	lua_pushinteger(l, FANN_TRAIN_BATCH);
	lua_setglobal(l, "FANN_TRAIN_BATCH");
	lua_pushinteger(l, FANN_TRAIN_RPROP);
	lua_setglobal(l, "FANN_TRAIN_RPROP");
	lua_pushinteger(l, FANN_TRAIN_QUICKPROP);
	lua_setglobal(l, "FANN_TRAIN_QUICKPROP");
	lua_pushinteger(l, FANN_TRAIN_SARPROP);
	lua_setglobal(l, "FANN_TRAIN_SARPROP");
}

LUA_FUNC(annCreate)
{
	UINT i = 0;
	UINT numLayers = (UINT)lua_tointeger(l, 1);
	UINT *layers = (UINT*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(UINT) * numLayers);
	for (i = 0; i < numLayers; i++)
		layers[i] = (UINT)luaL_checkinteger(l, i+2);

	struct fann *ann = fann_create_standard_array(numLayers, layers);
	HeapFree(GetProcessHeap(), 0, layers);

	if (ann == 0) lua_pushnil(l);
	else lua_pushinteger(l, PANN2UINT(ann));
	return 1;
}
LUA_FUNC(annCreateFromFile)
{
	PCHAR file = (PCHAR)lua_tostring(l, 1);
	struct fann *ann = fann_create_from_file(file);
	if (ann == 0) lua_pushnil(l);
	else lua_pushinteger(l, PANN2UINT(ann));
	return 1;
}
LUA_FUNC(annRun)
{
	struct fann *ann = UINT2PANN(lua_tointeger(l, 1));
	if (!lua_istable(l, 2) || ann == 0)
	{
		lua_pushnil(l);
		return 1;
	}

	float input[256];
	for (UINT i = 1; i <= fann_get_num_input(ann); i++)
	{
		lua_pushinteger(l, i);
		lua_gettable(l, -2);
		input[i-1] = (float)lua_tonumber(l, -1);
		lua_pop(l, 1);
	}

	float *output = fann_run(ann, input);

	lua_newtable(l);
	for (UINT i = 1; i <= fann_get_num_output(ann); i++)
	{
		lua_pushnumber(l, i);
		lua_pushnumber(l, output[i-1]);
		lua_rawset(l, -3);
	}
	return 1;
}
LUA_FUNC(annSaveToFile)
{
	struct fann *ann = UINT2PANN(lua_tointeger(l, 1));
	PCHAR file = (PCHAR)lua_tostring(l, 2);
	fann_save(ann, file);
	return 0;
}
LUA_FUNC(annDestroy)
{
	struct fann *ann = UINT2PANN(lua_tointeger(l, 1));
	fann_destroy(ann);
	return 0;
}

LUA_FUNC(annActivationSteepnessLayer)
{
	struct fann *ann = UINT2PANN(lua_tointeger(l, 1));
	if (lua_gettop(l) < 3)
	{
		lua_pushnil(l);
		return 1;
	}
	else
	{
		fann_set_activation_steepness_layer(ann,
			(fann_type)lua_tonumber(l, 2), (int)lua_tointeger(l, 3));
	}
	return 0;
}
LUA_FUNC(annActivationFunctionLayer)
{
	struct fann *ann = UINT2PANN(lua_tointeger(l, 1));
	if (lua_gettop(l) < 3)
	{
		lua_pushnil(l);
		return 1;
	}
	else
	{
		fann_set_activation_function_layer(ann,
			(fann_activationfunc_enum)lua_tointeger(l, 2), (int)lua_tointeger(l, 3));
	}
	return 0;
}
LUA_FUNC(annTrainStopFunction)
{
	struct fann *ann = UINT2PANN(lua_tointeger(l, 1));
	if (lua_gettop(l) < 2)
	{
		lua_pushnumber(l, (float)fann_get_train_stop_function(ann));
		return 1;
	}
	else
	{
		fann_set_train_stop_function(ann, (fann_stopfunc_enum)lua_tointeger(l, 2));
	}
	return 0;
}
LUA_FUNC(annBitFailLimit)
{
	struct fann *ann = UINT2PANN(lua_tointeger(l, 1));
	if (lua_gettop(l) < 2)
	{
		lua_pushnumber(l, (float)fann_get_bit_fail_limit(ann));
		return 1;
	}
	else
	{
		fann_set_bit_fail_limit(ann, (fann_type)lua_tonumber(l, 2));
	}
	return 0;
}
LUA_FUNC(annTrainAlgorithm)
{
	struct fann *ann = UINT2PANN(lua_tointeger(l, 1));
	if (lua_gettop(l) < 2)
	{
		lua_pushnumber(l, (float)fann_get_training_algorithm(ann));
		return 1;
	}
	else
	{
		fann_set_training_algorithm(ann, (fann_train_enum)lua_tointeger(l, 2));
	}
	return 0;
}
LUA_FUNC(annRandomizeWeights)
{
	struct fann *ann = UINT2PANN(lua_tointeger(l, 1));
	float minWeight = (float)lua_tonumber(l, 2);
	float maxWeight = (float)lua_tonumber(l, 3);
	fann_randomize_weights(ann, minWeight, maxWeight);
	return 0;
}
LUA_FUNC(annLearnRate)
{
	struct fann *ann = UINT2PANN(lua_tointeger(l, 1));
	if (lua_gettop(l) < 2)
	{
		lua_pushnumber(l, fann_get_learning_rate(ann));
		return 1;
	}
	else
	{
		fann_set_learning_rate(ann, (float)lua_tonumber(l, 2));
	}
	return 0;
}

LUA_FUNC(annTrain)
{
	struct fann *ann = UINT2PANN(lua_tointeger(l, 1));
	if (!lua_istable(l, 2) || !lua_istable(l, 3))
	{
		lua_pushnil(l);
		return 1;
	}
	lua_pop(l, 1); //top of stack is 2nd arg
	float input[256];
	for (UINT i = 1; i <= fann_get_num_input(ann); i++)
	{
		lua_pushinteger(l, i);
		lua_gettable(l, -2);
		input[i-1] = (float)lua_tonumber(l, -1);
		lua_pop(l, 1);
	}
	lua_pop(l, 1); //top of stack is 3nd arg
	float desired_output[256];
	for (UINT i = 1; i <= fann_get_num_output(ann); i++)
	{
		lua_pushinteger(l, i);
		lua_gettable(l, -2);
		input[i-1] = (float)lua_tonumber(l, -1);
		lua_pop(l, 1);
	}
	fann_train(ann, input, desired_output);
	return 0;
}
LUA_FUNC(annTrainOnData)
{
	struct fann *ann = UINT2PANN(lua_tointeger(l, 1));
	struct fann_train_data *data = UINT2PTRN(lua_tointeger(l, 2));
	float maxEpochs = (float)lua_tonumber(l, 3);
	float epochsBetweenReports = (float)lua_tonumber(l, 4);
	float desiredError = (float)lua_tonumber(l, 5);
	fann_train_on_data(ann, data, (UINT)maxEpochs,
		(UINT)epochsBetweenReports, desiredError);
	return 0;
}
LUA_FUNC(annTrainOnFile)
{
	struct fann *ann = UINT2PANN(lua_tointeger(l, 1));
	PCHAR file = (PCHAR)lua_tostring(l, 2);
	float maxEpochs = (float)lua_tonumber(l, 3);
	float epochsBetweenReports = (float)lua_tonumber(l, 4);
	float desiredError = (float)lua_tonumber(l, 5);
	fann_train_on_file(ann, file, (UINT)maxEpochs,
		(UINT)epochsBetweenReports, desiredError);
	return 0;
}
LUA_FUNC(annTrainEpoch)
{
	struct fann *ann = UINT2PANN(lua_tointeger(l, 1));
	struct fann_train_data *data = UINT2PTRN(lua_tointeger(l, 2));
	fann_train_epoch(ann, data);
	return 0;
}