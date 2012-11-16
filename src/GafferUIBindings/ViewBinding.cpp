//////////////////////////////////////////////////////////////////////////
//  
//  Copyright (c) 2012, John Haddon. All rights reserved.
//  
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions are
//  met:
//  
//      * Redistributions of source code must retain the above
//        copyright notice, this list of conditions and the following
//        disclaimer.
//  
//      * Redistributions in binary form must reproduce the above
//        copyright notice, this list of conditions and the following
//        disclaimer in the documentation and/or other materials provided with
//        the distribution.
//  
//      * Neither the name of John Haddon nor the names of
//        any other contributors to this software may be used to endorse or
//        promote products derived from this software without specific prior
//        written permission.
//  
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
//  IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
//  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
//  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
//  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
//  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
//  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
//  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
//  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
//  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//  
//////////////////////////////////////////////////////////////////////////

#include "boost/python.hpp"

#include "IECorePython/ScopedGILRelease.h"

#include "GafferBindings/NodeBinding.h"

#include "GafferUI/View.h"
#include "GafferUIBindings/ViewBinding.h"

using namespace boost::python;
using namespace Gaffer;
using namespace GafferUI;
using namespace GafferUIBindings;

static ContextPtr getContext( View &v )
{
	return v.getContext();
}

static ViewportGadgetPtr viewportGadget( View &v )
{
	return v.viewportGadget();
}

void GafferUIBindings::updateViewFromPlug( View &v )
{
	// the release is essential, as the update will most
	// likely involve evaluation of the graph from multiple
	// threads, and those threads might need access to python.
	IECorePython::ScopedGILRelease gilRelease;
	v.updateFromPlug();
}

void GafferUIBindings::bindView()
{
	GafferBindings::NodeClass<View>()
		.def( "getContext", &getContext )
		.def( "setContext", &View::setContext )
		.def( "viewportGadget", &viewportGadget )
		.def( "updateRequestSignal", &View::updateRequestSignal, return_internal_reference<1>() )
		.def( "_updateFromPlug", &updateViewFromPlug )
		.def( "create", &View::create )
		.staticmethod( "create" )
	;
}
