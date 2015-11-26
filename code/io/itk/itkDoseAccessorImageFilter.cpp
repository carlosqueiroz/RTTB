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
// @version $Revision: 4047 $ (last changed revision)
// @date    $Date: 2012-10-29 16:19:15 +0100 (Mo, 29 Okt 2012) $ (last change date)
// @author  $Author: zhang $ (last changed by)
*/


#include "itkDoseAccessorImageFilter.h"
#include "itkImageRegionIterator.h"
#include "itkImageRegionConstIteratorWithIndex.h"
#include "itkProgressReporter.h"

namespace itk
{
  /**
  * Constructor
  */
  DoseAccessorImageFilter
    ::DoseAccessorImageFilter()
  {
    this->SetNumberOfRequiredInputs(1);
  }

  void
    DoseAccessorImageFilter
    ::ThreadedGenerateData(const OutputImageRegionType & outputRegionForThread,
    ThreadIdType threadId)
  {
    ProgressReporter progress( this, threadId,
      outputRegionForThread.GetNumberOfPixels() );

    const unsigned int numberOfInputImages =
      static_cast< unsigned int >( this->GetNumberOfIndexedInputs() );

    const unsigned int numberOfOutputImages =
      static_cast< unsigned int >( this->GetNumberOfIndexedOutputs() );

    typedef ImageRegionConstIteratorWithIndex< InputImageType > ImageRegionConstIteratorType;
    typedef ImageRegionIterator< OutputImageType > OutputImageRegionIteratorType;

    InputImagePointer inputPtr = dynamic_cast< InputImageType * >( ProcessObject::GetInput(0) );
    ImageRegionConstIteratorType inputItr;
    if ( inputPtr )
    {
      inputItr = ImageRegionConstIteratorType(inputPtr, outputRegionForThread);
    }

    OutputImagePointer outputPtr = dynamic_cast< OutputImageType * >( ProcessObject::GetOutput(0) );
    OutputImageRegionIteratorType outputItr;
    if ( outputPtr )
    {
      outputItr = OutputImageRegionIteratorType(outputPtr, outputRegionForThread);
    }

    if ( inputPtr && outputPtr )
    {
      while ( !(outputItr.IsAtEnd()) )
      {
        ImageRegionConstIteratorType::IndexType index = inputItr.GetIndex();
        rttb::VoxelGridIndex3D doseIndex(index[0],index[1],index[2]);

        outputItr.Set(m_Accessor->getValueAt(doseIndex));

        ++outputItr;
        ++inputItr;

        progress.CompletedPixel();
      }
    }
  }
} // end namespace itk
