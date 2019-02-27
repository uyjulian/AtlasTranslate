#include "extension.h"
#include <Shared/Shrink.h>
#include <Shared/StringUtil.h>
#include <Shared/ProcessUtil.h>
#include <Shared/Atlas.h>

struct AtlasConfig atlcfg;

HANDLE mutex;

bool ProcessSentence(std::wstring& sentence, SentenceInfo sentenceInfo)
{
	if (!sentenceInfo["text number"] || !sentenceInfo["current select"])  {
		return false;
	}

	if (!mutex) {
		mutex = CreateMutex(NULL, FALSE, NULL);
		if (!mutex) {
			return false;
		}
	}
	bool waitingForMutex = true;
	while (waitingForMutex) {
		switch (WaitForSingleObject(mutex, INFINITE)) {
			case WAIT_OBJECT_0: {
				waitingForMutex = false;
				break;
			}
			case WAIT_ABANDONED: {
				return false;
			}
			default: {}
		}
	}
	if (!AtlasIsLoaded()) {
		atlcfg.flags = ~BREAK_ON_SINGLE_LINE_BREAKS;
		wcscpy(atlcfg.environment, L"Entertainment");
		wcscpy(atlcfg.trsPath, L"");
		InitAtlas(atlcfg, ATLAS_JAP_TO_ENG);
		if (!AtlasIsLoaded()) {
			ReleaseMutex(mutex);
			return false;
		}
	}
	wchar_t *otext = wcsdup(sentence.c_str());
	wchar_t *text = TranslateFull(otext, 0, 0, NULL, NULL);
	sentence += L"\n";
	sentence += text;
	free(otext);
	free(text);
	ReleaseMutex(mutex);
	return true;
}

