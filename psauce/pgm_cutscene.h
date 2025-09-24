

struct pcutscene_s
{
	char title[32];
	char text[256];
	char background[32];
	char audio[16];
};

// i think the .mlp files are masks to mask out the loading bar, so im not including them here


struct pgm_cutscene_s
{
	struct pcutscene_s pcutscene;
};