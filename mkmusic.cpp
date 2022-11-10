extern "C" { void _srand(); }


#include <fstream>
#include <iostream>
#include <cmath>

using namespace std;

const int sampleRate = 44100;
const int songLength = sampleRate * 120;

inline float mypow(float x,float y) {
	return pow(abs(x),y) * (x < 0 ? -1 : 1);
}

struct Instrument {
	float left;
	float right;
	float rands[1000];
	float a;
	
	Instrument(float a) {
		this->a = a;
		left = (float)rand() / (float)RAND_MAX;
		right = 1.0 - left;
		
		for(int i = 0;i < 1000;++i) rands[i] = (float)rand() / (float)RAND_MAX;
	}
	
	void render(float vol,int tone,float *buffers[2],int offset,int length) {
		float x = 441.0 / sampleRate * M_PI * pow(2.0,tone / 12.0);
	
		float xs[length];
		for(int i = 0;i < length;++i) xs[i] = 0;
		
		for(int i = 0;i < length;++i) {
			float sample = 
				rands[10] * sin(i * x)
				+ rands[11] * mypow(sin(i * x),2)
				+ rands[12] * mypow(sin(i * x),0.5)
				+ rands[13] * sin(i * x / 2)
				+ rands[14] * mypow(sin(i * x / 2),2)
				+ rands[15] * mypow(sin(i * x / 2),0.5);

			sample /= rands[10] + rands[11] + rands[12] + rands[13] + rands[14] + rands[15];
			
			sample *= (2 + cos(a * 0.1 * x * i * (rands[50] * 0.3 + 0.7) + M_PI * 2 * rands[51])) / 3;
			//sample *= (atan(20.0 * (rands[2] * 0.7 + 0.3) * i / 44100.0 - 0.1 * (rands[3] * 0.5 + 0.5)) + M_PI_2) / M_PI;
			xs[i] = sample;
		}
		
		float mx = -100000;
		const int n = 50;

		for(int i = 0;i < length - n - 1;++i) {
			float sum = 0;
			for(int j = 0;j < n;++j) sum += abs(xs[i + j]);
			sum /= n;
			
			if(sum > mx) mx = sum;
		}

		cout << mx << " ";
		mx = 1;

		for(int i = 0;i < length && i + offset < songLength;++i) {
			float f = (-atan(30.0 * (rands[0] * 0.7 + 0.3) * (0.1 + (i - length) / 44100.0)) + M_PI_2) / M_PI;
			buffers[0][i + offset] += vol * left * xs[i] / mx * f;
			buffers[1][i + offset] += vol * right * xs[i] / mx * f;
		}
	}
};





const int dur[] = {0,2,4,5,7,9,11};
const int ndur = sizeof(dur) / sizeof(dur[0]);

int scale[16];
int nscale = 0;

void makeScale() {
	int k = rand() % ndur;
	int k0 = k;
	int j = 0;
	int bias = (rand() % 5) + 5;
	nscale = 0;
	
	for(int i = 0;i < sizeof(scale) / sizeof(scale[0]);++i) {
		scale[i] = dur[k] + j + bias - dur[k0];
		if(scale[i] > 24) break;
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
	int tone;
	
	Pattern() : Instrument((4.0 * rand()) / RAND_MAX + 2.92){
		tone = rand() % (nscale / 2);
		//rands[0] = 1;
		//rands[1] = 0;
	}
	
	void render(float *buffers[2],int offset,int length) {
		Instrument::render(5,scale[tone] - 12,buffers,offset,length);
	}
};


struct Melody : Instrument {
	int prev;
	
	Melody() : Instrument((0.2 * rand() * rand()) / RAND_MAX / RAND_MAX + 0.01) {
		prev = scale[rand() % ndur];
		//rands[0] = 0;
		//rands[1] = 1;
	}
	
	void render(float *buffers[2],int offset,float lengthFactor) {
		int tone = prev;
		int k = rand() % 4;
		switch(k) {
			case 0: tone = rand() % nscale;break;
			case 1: tone = prev;break;
			case 2: tone = prev - 1;break;
			case 3: tone = prev + 1;break;
		}
		if(tone < 0) tone = 0;
		if(tone >= nscale) tone = nscale - 1;
		Instrument::render(0.8,scale[tone],buffers,offset,lengthFactor * sampleRate / 6.0 * (1.0 + rand() % 3));
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



int BPM = 90 + (rand() % 20);



int main() {
	_srand();
	
	static_assert(sizeof(wav_hdr) == 44, "");

	int fsize = songLength * 4;

	wav_hdr wav;
	wav.ChunkSize = fsize + sizeof(wav_hdr) - 8;
	wav.Subchunk2Size = fsize + sizeof(wav_hdr) - 44;

	std::ofstream out("test.wav", std::ios::binary);
	out.write(reinterpret_cast<const char *>(&wav), sizeof(wav));

	float *buffers[2] = {new float[songLength],new float[songLength]};
	
	makeScale();
	BPM = 90 + (rand() % 20);


	Pattern pats[4];
	Melody mels[6];
	int k = 0;

	for(int i = 0;i < songLength;i += sampleRate * 60 / BPM / 4) {
		for(int j = 0;j < sizeof(pats) / sizeof(pats[0]);++j)
			if(rand() % 100 < 30 )
				pats[j].render(buffers,i + rand() % 1000,sampleRate / 5);

		for(int j = 0;j < sizeof(mels) / sizeof(mels[0]);++j)
			if(rand() % 100 < 40 / (j + 1))
				mels[j].render(buffers,i + rand() % 1000,0.25 * (j / 2) + 1.0);

		int k2 = i / sampleRate / 15;
		if(k2 != k) {
			k = k2;
			makeScale();
		}
	}
	
	int16_t d;
	for (int i = 0; i < songLength; ++i) {
		d = buffers[0][i] * 1000.0;	
		out.write(reinterpret_cast<char *>(&d), sizeof(int16_t));
	//}
	//for (int i = 0; i < songLength; ++i) {
		d = buffers[1][i] * 1000.0;	
		out.write(reinterpret_cast<char *>(&d), sizeof(int16_t));
	}

	return 0;
}


