#include "extension.h"
#include <Shared/Shrink.h>
#include <Shared/Atlas.h>

struct AtlasConfig atlcfg;

std::mutex procMutex;

bool ProcessSentence(std::wstring& sentence, SentenceInfo sentenceInfo)
{
	if (!sentenceInfo["text number"] || !sentenceInfo["current select"])  {
		return false;
	}

	std::lock_guard<std::mutex> lock(procMutex);
	if (!AtlasIsLoaded()) {
		atlcfg.flags = ~BREAK_ON_SINGLE_LINE_BREAKS;
		wcscpy(atlcfg.environment, L"Entertainment");
		wcscpy(atlcfg.trsPath, L"");
		InitAtlas(atlcfg, ATLAS_JAP_TO_ENG);
		if (!AtlasIsLoaded()) {
			return false;
		}
	}
	wchar_t *otext = wcsdup(sentence.c_str());
	wchar_t *text = TranslateFull(otext, 0, 0, NULL, NULL);
	sentence += L"\n";
	sentence += text;
	free(otext);
	free(text);
	return true;
}

