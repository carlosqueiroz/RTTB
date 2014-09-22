// -----------------------------------------------------------------------
// RTToolbox - DKFZ radiotherapy quantitative evaluation library
//
// Copyright (c) German Cancer Research Center (DKFZ),
// Software development for Integrated Diagnostics and Therapy (SIDT).
// ALL RIGHTS RESERVED.
// See rttbCopyright.txt or
// http://www.dkfz.de/en/sidt/projects/rttb/copyright.html
//
// This software is distributed WITHOUT ANY WARRANTY; without even
// the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
// PURPOSE.  See the above copyright notices for more information.
//
//------------------------------------------------------------------------
/*!
// @file
// @version $Revision$ (last changed revision)
// @date    $Date$ (last change date)
// @author  $Author$ (last changed by)
*/
#ifndef __DOSE_ACCESSOR_GENERATOR_INTERFACE_H
#define __DOSE_ACCESSOR_GENERATOR_INTERFACE_H

#include <boost/shared_ptr.hpp>

#include "rttbDoseAccessorInterface.h"

namespace rttb{
	namespace core
		{
		/*! @class DoseAccessorGeneratorInterface
			@brief Interface for all DoseAccessor generating classes
		*/
		class DoseAccessorGeneratorInterface
			{
			public:
				typedef core::DoseAccessorInterface::DoseAccessorPointer DoseAccessorPointer;

			
			private:
				DoseAccessorGeneratorInterface(const DoseAccessorGeneratorInterface&); //not implemented on purpose -> non-copyable
				DoseAccessorGeneratorInterface& operator=(const DoseAccessorGeneratorInterface&);//not implemented on purpose -> non-copyable
				
				
			protected:	
				DoseAccessorGeneratorInterface() {};
				virtual ~DoseAccessorGeneratorInterface() {};

			public: 
				
				
				/*! @brief Generate DoseAccessor 
					@return Return shared pointer of DoseAccessor. 
				*/
				virtual DoseAccessorPointer generateDoseAccessor() = 0;
			};
		}
	}

#endif