/**************************************************************************
    Lightspark, a free flash player implementation

    Copyright (C) 2025  Ludger Krämer <dbluelle@onlinehome.de>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
**************************************************************************/

#include "scripting/abc.h"
#include "scripting/abc_optimized.h"
#include "scripting/abc_optimized_convert_s.h"

using namespace std;
using namespace lightspark;

void lightspark::abc_convert_s_constant(call_context* context)
{
	LOG_CALL("convert_s_c");
	asAtom res = *context->exec_pos->arg1_constant;
	if(!asAtomHandler::isString(res))
	{
		tiny_string s = asAtomHandler::toString(res,context->worker);
		asAtomHandler::replace(res,(ASObject*)abstract_s(context->worker,s));
	}
	RUNTIME_STACK_PUSH(context,res);
	++(context->exec_pos);
}
void lightspark::abc_convert_s_local(call_context* context)
{
	LOG_CALL("convert_s_l:"<<asAtomHandler::toDebugString(CONTEXT_GETLOCAL(context,context->exec_pos->local_pos1)));
	asAtom res =CONTEXT_GETLOCAL(context,context->exec_pos->local_pos1);
	if(!asAtomHandler::isString(res))
	{
		tiny_string s = asAtomHandler::toString(res,context->worker);
		ASATOM_DECREF(res);
		asAtomHandler::replace(res,(ASObject*)abstract_s(context->worker,s));
	}
	else
		ASATOM_INCREF(res);
	RUNTIME_STACK_PUSH(context,res);
	++(context->exec_pos);
}
void lightspark::abc_convert_s_constant_localresult(call_context* context)
{
	LOG_CALL("convert_s_cl");
	asAtom res = *context->exec_pos->arg1_constant;
	if(!asAtomHandler::isString(res))
	{
		tiny_string s = asAtomHandler::toString(res,context->worker);
		ASATOM_DECREF(res);
		asAtomHandler::replace(res,(ASObject*)abstract_s(context->worker,s));
	}
	REPLACELOCALRESULT(context,context->exec_pos->local3.pos,res);
	++(context->exec_pos);
}
void lightspark::abc_convert_s_local_localresult(call_context* context)
{
	asAtom res = CONTEXT_GETLOCAL(context,context->exec_pos->local_pos1);
	LOG_CALL("convert_s_ll "<<asAtomHandler::toDebugString(res)<<" "<<asAtomHandler::getObject(res)<<" "<< context->exec_pos->local_pos1<<" "<<(context->exec_pos->local3.pos));
	if(!asAtomHandler::isString(res))
	{
		tiny_string s = asAtomHandler::toString(res,context->worker);
		asAtomHandler::replace(res,(ASObject*)abstract_s(context->worker,s));
	}
	else
		ASATOM_INCREF(res);
	REPLACELOCALRESULT(context,context->exec_pos->local3.pos,res);
	++(context->exec_pos);
}
void lightspark::abc_convert_s_constant_setslotnocoerce(call_context* context)
{
	LOG_CALL("convert_s_cs");
	asAtom res = *context->exec_pos->arg1_constant;
	if(!asAtomHandler::isString(res))
	{
		tiny_string s = asAtomHandler::toString(res,context->worker);
		ASATOM_DECREF(res);
		asAtomHandler::replace(res,(ASObject*)abstract_s(context->worker,s));
	}
	asAtom obj = CONTEXT_GETLOCAL(context,context->exec_pos->local3.pos);
	uint32_t t = context->exec_pos->local3.flags & ~ABC_OP_BITMASK_USED;
	asAtomHandler::getObjectNoCheck(obj)->setSlotNoCoerce(t,res,context->worker);
	++(context->exec_pos);
}
void lightspark::abc_convert_s_local_setslotnocoerce(call_context* context)
{
	LOG_CALL("convert_s_ls");
	asAtom res = CONTEXT_GETLOCAL(context,context->exec_pos->local_pos1);
	if(!asAtomHandler::isString(res))
	{
		tiny_string s = asAtomHandler::toString(res,context->worker);
		ASATOM_DECREF(res);
		asAtomHandler::replace(res,(ASObject*)abstract_s(context->worker,s));
	}
	asAtom obj = CONTEXT_GETLOCAL(context,context->exec_pos->local3.pos);
	uint32_t t = context->exec_pos->local3.flags & ~ABC_OP_BITMASK_USED;
	asAtomHandler::getObjectNoCheck(obj)->setSlotNoCoerce(t,res,context->worker);
	++(context->exec_pos);
}
