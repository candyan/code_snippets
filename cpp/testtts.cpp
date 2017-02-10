#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "TtsEngine.h"

#define OUTPUT_BUFFER_SIZE (128 * 1024)

using namespace android;

static bool synthesis_complete = false;

static FILE *outfp = stdout;

// @param [inout] void *&       - The userdata pointer set in the original
//                                 synth call
// @param [in]    uint32_t      - Track sampling rate in Hz
// @param [in] tts_audio_format - The audio format
// @param [in]    int           - The number of channels
// @param [inout] int8_t *&     - A buffer of audio data only valid during the
//                                execution of the callback
// @param [inout] size_t  &     - The size of the buffer
// @param [in] tts_synth_status - indicate whether the synthesis is done, or
//                                 if more data is to be synthesized.
// @return TTS_CALLBACK_HALT to indicate the synthesis must stop,
//         TTS_CALLBACK_CONTINUE to indicate the synthesis must continue if
//            there is more data to produce.
tts_callback_status synth_done(void *& userdata, uint32_t sample_rate,
        tts_audio_format audio_format, int channels, int8_t *& data, size_t& size, tts_synth_status status)
{
	//fprintf(stderr, "TTS callback, rate: %d, data size: %d, status: %i\n", sample_rate, size, status);

	if (status == TTS_SYNTH_DONE)
	{
		synthesis_complete = true;
	}

	if ((size == OUTPUT_BUFFER_SIZE) || (status == TTS_SYNTH_DONE))
	{
		fwrite(data, size, 1, outfp);
	}

	return TTS_CALLBACK_CONTINUE;
}

static void usage(void)
{
	fprintf(stderr, "\nUsage:\n\n" \
					"testtts [-l lang] [-o filename] \"Text to speak\"\n\n" \
		   			"  -o\tFile to write audio to (default stdout)\n" \
						"  -l\tLanguage (en,us,de,fr,es,it)\n" );
	exit(0);
}

int main(int argc, char *argv[])
{
	tts_result result;
	TtsEngine* ttsEngine = getTtsEngine();
	uint8_t* synthBuffer;
	char* synthInput = NULL;
	int currentOption;
	char* outputFilename = NULL;

	int lang = 0;
	char* langName = NULL;
	static const char* languages[6][3] = { 
		{"en","eng","GBR"},
		{"us","eng","US"},
		{"de","deu","DEU"},
		{"fr","fra","FRA"},
		{"es","spa","ESP"},
		{"it","ita","ITA"}
	};

	fprintf(stderr, "Pico TTS Test App\n");

	if (argc == 1)
	{
		usage();
	}

    while ( (currentOption = getopt(argc, argv, "o:l:h")) != -1)
    {
        switch (currentOption)
        {
        case 'o':
        	outputFilename = optarg;
            fprintf(stderr, "Output audio to file '%s'\n", outputFilename);
            break;
        case 'l':
						{
							langName = optarg;
							int lnum = sizeof(languages)/sizeof(*languages);
							for( int i=0; i<lnum; ++i){
								if( strcmp(langName, languages[i][0]) == 0 ) lang = i;
							}
						}
            break;
        case 'h':
        	usage();
            break;
				case '?':
						if (optopt == 'l' || optopt == 'o')
							fprintf (stderr, "Option -%c requires an argument.\n", optopt);
				default:
						printf ("Getopt returned character code 0%o ??\n", currentOption);
        }
    }

    fprintf(stderr, "Language: '%s'\n", languages[lang][0] );

    if (optind < argc)
    {
    	synthInput = argv[optind];
    }

    if (!synthInput)
    {
    	fprintf(stderr, "Error: no input string\n");
    	usage();
			exit(1);
    }

    fprintf(stderr, "Input string: \"%s\"\n", synthInput);

	synthBuffer = new uint8_t[OUTPUT_BUFFER_SIZE];

	result = ttsEngine->init(synth_done, "../lang/");

	if (result != TTS_SUCCESS)
	{
		fprintf(stderr, "Failed to init TTS\n");
	}

	// Set language which was optional given by -l flag 
	result = ttsEngine->setLanguage(languages[lang][1], languages[lang][2], "");

	if (result != TTS_SUCCESS)
	{
		fprintf(stderr, "Failed to load language\n");
	}

	if (outputFilename)
	{
		outfp = fopen(outputFilename, "wb");
	}

	fprintf(stderr, "Synthesising text...\n");

	result = ttsEngine->synthesizeText(argv[argc-1], synthBuffer, OUTPUT_BUFFER_SIZE, NULL);

	if (result != TTS_SUCCESS)
	{
		fprintf(stderr, "Failed to synth text\n");
	}

	while(!synthesis_complete)
	{
		usleep(100);
	}

	fprintf(stderr, "Completed.\n");

	if (outputFilename)
	{
		fclose(outfp);
	}

	result = ttsEngine->shutdown();

	if (result != TTS_SUCCESS)
	{
		fprintf(stderr, "Failed to shutdown TTS\n");
	}

	delete [] synthBuffer;

	return 0;
}

