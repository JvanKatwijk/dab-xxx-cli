#
/*
 *    Copyright (C) 2020
 *    Jan van Katwijk (J.vanKatwijk@gmail.com)
 *    Lazy Chair Computing
 *
 *    This file is part of dab-xxx-cli
 *
 *    dab-xxx-cli is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    dab-xxx-cli is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with dab-xxx-cli; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *	Use the fdk-aac library.
 */
#ifdef	__WITH_FDK_AAC__
#ifndef	__FDK_AAC__
#define	__FDK_AAC__

#include	<stdint.h>
#include	<aacdecoder_lib.h>
#include	"ringbuffer.h"
#include	"dab-api.h"

typedef struct {
        int     rfa;
        int     dacRate;
        int     sbrFlag;
        int     psFlag;
        int     aacChannelMode;
        int     mpegSurround;
        int     CoreChConfig;
        int     CoreSrIndex;
        int     ExtensionSrIndex;
} stream_parms;

//
/**
  *	fdkAAC is an interface to the fdk-aac library,
  *	using the LOAS protocol
  */
class	fdkAAC {
public:
		fdkAAC	(audioOut_t, void *);
		~fdkAAC	();

int16_t		MP42PCM (stream_parms *sp,
                         uint8_t   packet [],
                         int16_t   packetLength);
private:
	audioOut_t		soundOut;
	void			*userData;
	void			output		(int16_t *, int, bool, int);
	RingBuffer<int16_t>	*audioBuffer;
	bool			working;
	HANDLE_AACDECODER	handle;
};

#endif
#endif