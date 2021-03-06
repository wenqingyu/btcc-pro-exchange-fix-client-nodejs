/*
 * FixStartWorker.cpp
 *
 *  Created on: Jul 27, 2014
 *      Author: stefankutko
 */

#include <node.h>
#include <nan.h>

#include "quickfix/Exceptions.h"
#include "quickfix/SocketInitiator.h"
#include "FixInitiatorStartWorker.h"

using namespace v8;
using namespace node;

// Executed inside the worker-thread.
// It is not safe to access V8, or V8 data structures
// here, so everything we need for input and output
// should go on `this`.
void FixInitiatorStartWorker::Execute () {
	try {
		initiator->start();
	} catch(FIX::ConfigError& e) {
		//handle this exception
	}
}

// Executed when the async work is complete
// this function will be run inside the main event loop
// so it is safe to use V8 again
void FixInitiatorStartWorker::HandleOKCallback () {
	Nan::HandleScope scope;

	if(!callback->IsEmpty()) {
		Local<Value> argv[] = {
			Nan::Null()
		};

		callback->Call(1, argv);
	}
}
