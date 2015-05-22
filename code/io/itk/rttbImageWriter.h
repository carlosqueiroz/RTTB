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
// @version $Revision: 793 $ (last changed revision)
// @date    $Date: 2014-10-10 10:24:45 +0200 (Fr, 10 Okt 2014) $ (last change date)
// @author  $Author: lzhang $ (last changed by)
*/

#ifndef __RTTB_IMAGE_WRITER_H
#define __RTTB_IMAGE_WRITER_H

#include "itkImage.h"
#include "itkImageSource.h"
#include "itkImageFileWriter.h"
#include "rttbBaseType.h"
#include "rttbITKImageMaskAccessor.h"

namespace rttb
{
	namespace io
	{
		namespace itk {


			/** @class ImageWriter
			* @brief Helper class writing 3D images to file ...
			*
			*/
			class ImageWriter
			{
				typedef ::itk::Image<DoseTypeGy, 3> ITKMaskImageType;
				typedef ITKMaskImageType::Pointer ITKImageTypePointer;
				typedef ::itk::ImageFileWriter<ITKMaskImageType> WriterType;

			private:
				FileNameString _fileName;
				ITKImageTypePointer _itkImage;


			public:
				ImageWriter(FileNameString aFileName, ITKImageTypePointer aITKImage);

				/*! @brief Write itk image to file
				@return Return true if successful.
				@exception InvalidParameterException thrown if itk exception by writing the image
				*/
				bool writeFile();



			};
		}//end namespace itk
	}//end namespace io
}//end namespace rttb


#endif