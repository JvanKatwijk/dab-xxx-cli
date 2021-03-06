#
/*
 *    Copyright (C) 2020
 *    Jan van Katwijk (J.vanKatwijk@gmail.com)
 *    Lazy Chair Computing
 *
 *    This file is part of terminal-DAB
 *
 *    terminal-DAB is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    terminal-DAB is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with terminal-DAB; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#
#ifndef	__MSC_HANDLER__
#define	__MSC_HANDLER__

#include	<stdio.h>
#include	<stdint.h>
#include	<thread>
#include	<vector>
#include	<mutex>
#include	<atomic>
#include	"dab-constants.h"
#include	"dab-api.h"
#include	"dab-params.h"
#include	"freq-interleaver.h"
#include	"fft_handler.h"
#include	"semaphore.h"

class	virtualBackend;

using namespace std;
class mscHandler {
public:
			mscHandler		(parameters	*,
	                                         RingBuffer<std::complex<int16_t>> *,
	                                 	 void		*);
			~mscHandler		(void);
	void		process_mscBlock	(std::complex<float> *,
	                                                     int16_t);
	void		set_audioChannel	(audiodata	*);
//	void		set_dataChannel		(packetdata     *);
	void		reset			(void);
	void		stop			(void);
	void		start			(void);
private:
	parameters	*the_parameters;
	RingBuffer<std::complex<int16_t>>	*pcmBuffer;
virtual	void		run			(void);
	void		process_mscBlock	(std::vector<int16_t>,
	                                                      int16_t);
	dabParams	params;
	fft_handler	my_fftHandler;
	std::complex<float>	*fft_buffer;
	interLeaver	myMapper;
	void		*userData;
	Semaphore       freeSlots;
        Semaphore       usedSlots;
        std::complex<float>  **theData;
	std::atomic<bool>	running;

	std::thread	threadHandle;
	std::vector<complex<float> > phaseReference;
	std::mutex	mutexer;
	std::vector<virtualBackend *>theBackends;
	int16_t		cifCount;
	int16_t		BitsperBlock;
	int16_t		numberofblocksperCIF;
};

#endif

