extern "C" { long long _rand(); }
extern "C" { long long _srand(); }

#include <fstream>
#include <iostream>
#include <cmath>

using namespace std;

const long long sampleRate = 44100;
const long long songLength = sampleRate * 120;

inline float mypow(float x,float y) {
	return pow(abs(x),y) * (x < 0 ? -1 : 1);
}

const long long TONES_PER_OCTAVE = 12;

struct Instrument {
	float left;
	float right;
	float rands[44100];
	float a;
	
	Instrument(float a) {
		this->a = a;
		left = (float)_rand() / (float)RAND_MAX;
		right = 1.0 - left;
		
		const long long m = 16;
		float r1[m];
		for(long long i = 0;i < m;++i) r1[i] = (float)_rand() / (float)RAND_MAX - 0.5;
		
		float max = -100000;
		float min = 100000;
		for(long long i = 0;i < m;++i) if(r1[i] > max) max = r1[i]; 
		for(long long i = 0;i < m;++i) if(r1[i] < min) min = r1[i]; 
		for(long long i = 0;i < m;++i) r1[i] = 2 * ((r1[i] - min) / (max - min) - 0.5);

		for(long long k = 0;k < 0;++k) {
			float r2[m];
			for(long long i = 0;i < m;++i) {
				r2[i] = 0;	
				for(long long j = 0;j < m;++j) r2[i] += r1[i] * r1[m - j - 1];
			}

			float max = 0;
			for(long long i = 0;i < m;++i) if(abs(r2[i]) > max) max = abs(r2[i]); 
			for(long long i = 0;i < m;++i) r1[i] = r2[i] / max;
		}

		const long long n = sizeof(rands) / sizeof(*rands) / m;
		for(long long i = 0;i < sizeof(rands) / sizeof(*rands);++i) {
			long long j = i / n;
			long long k = i % n;
			rands[i] = (k * r1[j + 1] / n) + ((n - k) * r1[j] / n);
		}

		for(long long i = 0;i < m;++i) cout << r1[i] << " ";
		cout << endl << endl << "********************" << endl << endl;
	}
	
	void render(float vol,long long tone,float *buffers[2],long long offset,long long length) {
		float y = pow(2.0,tone / (float)TONES_PER_OCTAVE);
		float x = 441.0 / sampleRate * M_PI * y;
	
		float xs[length];
		for(long long i = 0;i < length;++i) xs[i] = 0;
		
		for(long long i = 0;i < length;++i) {
			long long j = (long long)round(32 * i * y * sizeof(rands) / sizeof(*rands) / length);
			xs[i] = (rands[j % (sizeof(rands) / sizeof(*rands))] * 0.1 + 0.9) * sin(x*i);
		}
		
		for(long long i = 0;i < length && i + offset < songLength;++i) {
			buffers[0][i + offset] += vol * left * xs[i];
			buffers[1][i + offset] += vol * right * xs[i];
		}
	}
};





const long long dur[] = {0,2,4,5,7,9,11};
const long long ndur = sizeof(dur) / sizeof(dur[0]);

long long scale[50];
long long nscale = 0;

void makeScale2() {
	long long k = _rand() % 5 + 5;
	nscale = 0;
	for(long long i = 0;i < sizeof(scale) / sizeof(scale[0]);++i) {
		scale[i] = k;
		if(scale[i] > 1.5 * TONES_PER_OCTAVE) break;
		cout << scale[i] << " ";
		nscale += 1;

		if(_rand() % 100 < 33)
			k += 1;
		else
			k += 2;
	}
	cout << endl;
}

void makeScale() {
	long long k = _rand() % ndur;
	long long k0 = k;
	long long j = 0;
	long long bias = (_rand() % 5) + 5;
	nscale = 0;
	
	for(long long i = 0;i < sizeof(scale) / sizeof(scale[0]);++i) {
		scale[i] = dur[k] + j + bias - dur[k0];
		if(scale[i] > 34) break;
		cout << scale[i] << " ";

		nscale += 1;

		k += 1;
		if(k >= ndur) {
			k = 0;
			j += 12;
		}
	}

	cout << endl;
}


struct Pattern : Instrument {
	long long tone;
	
	Pattern() : Instrument((4.0 * _rand()) / RAND_MAX + 2.92){
		tone = _rand() % (nscale / 2);
		//rands[0] = 1;
		//rands[1] = 0;
	}
	
	void render(float *buffers[2],long long offset,long long length) {
		Instrument::render(3,scale[tone] - 12,buffers,offset,length);
	}
};


struct Melody : Instrument {
	long long prev;
	
	Melody() : Instrument((0.2 * _rand() * _rand()) / RAND_MAX / RAND_MAX + 0.01) {
		prev = scale[_rand() % ndur];
		//rands[0] = 0;
		//rands[1] = 1;
	}
	
	void render(float *buffers[2],long long offset,float lengthFactor) {
		long long tone = prev;
		long long k = _rand() % 4;
		switch(k) {
			case 0: tone = _rand() % nscale;break;
			case 1: tone = prev;break;
			case 2: tone = prev - 1;break;
			case 3: tone = prev + 1;break;
		}
		if(tone < 0) tone = 0;
		if(tone >= nscale) tone = nscale - 1;
		Instrument::render(1,scale[tone],buffers,offset,lengthFactor * sampleRate / 6.0 * (1.0 + _rand() % 3));
		prev = tone;
	}
};


typedef struct WAV_HEADER {
	/* RIFF Chunk Descriptor */
	uint8_t RIFF[4] = {'R', 'I', 'F', 'F'}; // RIFF Header Magic header
	uint32_t ChunkSize;                     // RIFF Chunk Size
	uint8_t WAVE[4] = {'W', 'A', 'V', 'E'}; // WAVE Header
	/* "fmt" sub-chunk */
	uint8_t fmt[4] = {'f', 'm', 't', ' '}; // FMT header
	uint32_t Subchunk1Size = 16;           // Size of the fmt chunk
	uint16_t AudioFormat = 1; // Audio format 1=PCM,6=mulaw,7=alaw,     257=IBM
		                    // Mu-Law, 258=IBM A-Law, 259=ADPCM
	uint16_t NumOfChan = 2;   // Number of channels 1=Mono 2=Sterio
	uint32_t SamplesPerSec = sampleRate;   // Sampling Frequency in Hz
	uint32_t bytesPerSec = sampleRate * 4; // bytes per second
	uint16_t blockAlign = 4;          // 2=16-bit mono, 4=16-bit stereo
	uint16_t bitsPerSample = 16;      // Number of bits per sample
	/* "data" sub-chunk */
	uint8_t Subchunk2ID[4] = {'d', 'a', 't', 'a'}; // "data"  string
	uint32_t Subchunk2Size;                        // Sampled data length
} wav_hdr;



long long BPM;



int main() {
	_srand();

	BPM = 90 + (_rand() % 20);

	//for(int i = 0;i < 10;++i) cout << _rand() << endl;
	//exit(0);
	
	static_assert(sizeof(wav_hdr) == 44, "");

	long long fsize = songLength * 4;

	wav_hdr wav;
	wav.ChunkSize = fsize + sizeof(wav_hdr) - 8;
	wav.Subchunk2Size = fsize + sizeof(wav_hdr) - 44;

	std::ofstream out("test.wav", std::ios::binary);
	out.write(reinterpret_cast<const char *>(&wav), sizeof(wav));

	float *buffers[2] = {new float[songLength],new float[songLength]};
	
	makeScale2();
	BPM = 90 + (_rand() % 10);


	Pattern pats[4];
	Melody mels[6];
	long long k = 0;

	for(long long i = 0;i < songLength;i += sampleRate * 60 / BPM / 4) {
		/*
		for(long long j = 0;j < sizeof(pats) / sizeof(pats[0]);++j)
			if(_rand() % 100 < 20 )
				pats[j].render(buffers,i + _rand() % 1000,sampleRate / 5);
*/
		for(long long j = 0;j < sizeof(mels) / sizeof(mels[0]);++j)
			if(_rand() % 100 < 40 / pow(j + 1,0.1))
				mels[j].render(buffers,i + _rand() % 1000,1.0);

		long long k2 = i / sampleRate / 15;
		if(k2 != k) {
			k = k2;
			makeScale2();
		}
	}
	
	int16_t d;
	for (long long i = 0; i < songLength; ++i) {
		d = buffers[0][i] * 1000.0;	
		out.write(reinterpret_cast<char *>(&d), sizeof(int16_t));
	//}
	//for (long long i = 0; i < songLength; ++i) {
		d = buffers[1][i] * 1000.0;	
		out.write(reinterpret_cast<char *>(&d), sizeof(int16_t));
	}

	return 0;
}


