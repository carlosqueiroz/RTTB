// -----------------------------------------------------------------------
// MatchPoint - DKFZ translational registration framework
//
// Copyright (c) German Cancer Research Center (DKFZ),
// Software development for Integrated Diagnostics and Therapy (SIDT).
// ALL RIGHTS RESERVED.
// See mapCopyright.txt or
// http://www.dkfz.de/en/sidt/projects/MatchPoint/copyright.html
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
// Subversion HeadURL: $HeadURL: https://svn/sbr/Sources/SBR-Projects/MatchPoint/trunk/Code/IO/include/mapImageReader.tpp $
*/

#ifndef __RTTB_ITK_IMAGE_FILE_DOSE_ACCESSOR_GENERATOR_TPP
#define __RTTB_ITK_IMAGE_FILE_DOSE_ACCESSOR_GENERATOR_TPP

#include "rttbITKImageFileDoseAccessorGenerator.h"
#include "rttbInvalidParameterException.h"
#include "rttbInvalidDoseException.h"
#include "rttbITKImageDoseAccessor.h"

namespace rttb
{
	namespace io
	{
		namespace itk
		{

			template <typename TPixelType> void ITKImageFileDoseAccessorGenerator::doCasting(
			    GenericImageReader::GenericOutputImageType* genericImage)
			{
				typedef ::itk::Image<TPixelType, 3> InputImageType;
				typedef ITKDoseImageType OutputImageType;
				InputImageType::Pointer pCastedInput = dynamic_cast<InputImageType*>(genericImage);
				typedef ::itk::CastImageFilter<InputImageType, OutputImageType> CastFilterType;
				CastFilterType::Pointer castFilter = CastFilterType::New();
				castFilter->SetInput(pCastedInput);

				try
				{
					//important to update the filter!
					castFilter->Update();
					_itkDoubleImage = castFilter->GetOutput();
				}
				catch (::itk::ExceptionObject& e)
				{
					std::cerr << "ITK Error!!!" << std::endl;
					std::cerr << e << std::endl;
				}
			}

		}
	}
}
#endif