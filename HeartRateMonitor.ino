#include "arduinoFFT.h"
#include "Metro.h"

#define SCL_INDEX 0x00
#define SCL_TIME 0x01
#define SCL_FREQUENCY 0x02

const uint16_t samples = 256;
const double samplingFrequency = 16;
const int delay_ms = 1000/samplingFrequency;

Metro sampler = Metro(delay_ms);

const uint16_t LPF = (0.5/samplingFrequency)*samples;
const uint16_t HPF = (2.0/samplingFrequency)*samples;


double vReal[samples];
double vImag[samples];
arduinoFFT FFT;

void setup() {
  Serial.begin(115200);
  //Serial.println("Start");
  pinMode(A0,INPUT);

  FFT = arduinoFFT();
}

void loop() {
  Serial.println("Measuring:-");
  int i=0;
  while(i<samples) {
    if(sampler.check() == 1) {
      if(i%16 == 0) Serial.println(".");
    
      vReal[i] = analogRead(A0)/1024.0;
      vImag[i] = 0;

      //Serial.print(i);
      //Serial.print(" ");
      //Serial.println(vReal[i]);
      i++;
    }
  }
  Serial.println();

  //FFT.Windowing(vReal, samples, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(vReal, vImag, samples, FFT_FORWARD);
  FFT.ComplexToMagnitude(vReal, vImag, samples);
  Serial.println("FFT:-");
  PrintVector(vReal, LPF, HPF, SCL_FREQUENCY);

  uint16_t peak = LPF;
  double peakMag = vReal[LPF];
  for(int i=LPF+1; i<HPF; i++) {
    if(vReal[i] > peakMag) {
      peakMag = vReal[i];
      peak = i;
    }
  }
  double peakFreq = (60.0*samplingFrequency*peak)/samples;
  Serial.print("Heart rate:");
  Serial.println(peakFreq, 3);
}

void PrintVector(double *vData, uint16_t start, uint16_t bufferSize, uint8_t scaleType)
{
  for (uint16_t i = start; i < bufferSize; i++)
  {
    double abscissa;
    /* Print abscissa value */
    switch (scaleType)
    {
      case SCL_INDEX:
        abscissa = (i * 1.0);
  break;
      case SCL_TIME:
        abscissa = ((i * 1.0) / samplingFrequency);
  break;
      case SCL_FREQUENCY:
        abscissa = ((i * 1.0 * samplingFrequency) / samples);
  break;
    }
    Serial.print(abscissa, 6);
    Serial.print(" ");
    Serial.print(vData[i], 4);
    Serial.println();
  }
  Serial.println();
}
