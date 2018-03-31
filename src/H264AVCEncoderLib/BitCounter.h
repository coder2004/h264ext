/*
********************************************************************************

COPYRIGHT AND WARRANTY INFORMATION

Copyright 2009-2012, International Telecommunications Union, Geneva

The Fraunhofer HHI hereby donate this source code to the ITU, with the following
understanding:
    1. Fraunhofer HHI retain the right to do whatever they wish with the
       contributed source code, without limit.
    2. Fraunhofer HHI retain full patent rights (if any exist) in the technical
       content of techniques and algorithms herein.
    3. The ITU shall make this code available to anyone, free of license or
       royalty fees.

DISCLAIMER OF WARRANTY

These software programs are available to the user without any license fee or
royalty on an "as is" basis. The ITU disclaims any and all warranties, whether
express, implied, or statutory, including any implied warranties of
merchantability or of fitness for a particular purpose. In no event shall the
contributor or the ITU be liable for any incidental, punitive, or consequential
damages of any kind whatsoever arising from the use of these programs.

This disclaimer of warranty extends to the user of these programs and user's
customers, employees, agents, transferees, successors, and assigns.

The ITU does not represent or warrant that the programs furnished hereunder are
free of infringement of any third-party patents. Commercial implementations of
ITU-T Recommendations, including shareware, may be subject to royalty fees to
patent holders. Information regarding the ITU-T patent policy is available from 
the ITU Web site at http://www.itu.int.

THIS IS NOT A GRANT OF PATENT RIGHTS - SEE THE ITU-T PATENT POLICY.

********************************************************************************
*/

#if !defined(AFX_BITCOUNTER_H__5062A2A9_6E04_4211_A337_9BDED6D88A82__INCLUDED_)
#define AFX_BITCOUNTER_H__5062A2A9_6E04_4211_A337_9BDED6D88A82__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BitWriteBufferIf.h"


H264AVC_NAMESPACE_BEGIN

class BitCounter :
public BitWriteBufferIf
{
public:

  BitWriteBufferIf* getNextBitWriteBuffer( Bool bStartNewBitstream ) { return NULL; }
  Bool              nextBitWriteBufferActive() { return false; }
  UChar*            getNextBuffersPacket()  { return NULL; }

  static ErrVal create( BitCounter*& rpcBitCounter );
  ErrVal destroy();

  ErrVal init()                                           { m_uiBitCounter = 0; return Err::m_nOK; }
  ErrVal uninit()                                         { m_uiBitCounter = 0; return Err::m_nOK; }

  BitCounter();
  virtual ~BitCounter();
  ErrVal write( UInt uiBits, UInt uiNumberOfBits = 1)     { m_uiBitCounter += uiNumberOfBits; return Err::m_nOK; }

  ErrVal pcmSamples( const TCoeff* pCoeff, UInt uiNumberOfSamples ) { m_uiBitCounter+=8*uiNumberOfSamples; return Err::m_nERR; }

  UInt getNumberOfWrittenBits()                           { return m_uiBitCounter; }

  Bool isByteAligned()                                    { return (0 == (m_uiBitCounter & 0x03)); }
  Bool isWordAligned()                                    { return (0 == (m_uiBitCounter & 0x1f)); }

  ErrVal writeAlignZero()                                 { return Err::m_nERR; }
  ErrVal writeAlignOne()                                  { return Err::m_nERR; }
  ErrVal flushBuffer()                                    { m_uiBitCounter = 0; return Err::m_nOK; }

  ErrVal   getLastByte(UChar &uiLastByte, UInt &uiLastBitPos) { return Err::m_nERR;} //FIX_FRAG_CAVLC

	//JVT-X046 {
	void loadBitWriteBuffer(BitWriteBufferIf* pcBitWriteBufferIf)	{}
	void loadBitCounter(BitWriteBufferIf* pcBitWriteBufferIf)
	{
		BitCounter* pcBitCounter = (BitCounter*)(pcBitWriteBufferIf);
		m_uiBitCounter = pcBitCounter->getNumberOfWrittenBits();
	}
	UInt getBitsWritten(void) { return 0; }
	//JVT-X046 }

private:
  UInt m_uiBitCounter;
};


H264AVC_NAMESPACE_END

#endif // !defined(AFX_BITCOUNTER_H__5062A2A9_6E04_4211_A337_9BDED6D88A82__INCLUDED_)
