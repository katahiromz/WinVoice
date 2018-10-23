// WinVoiceTest.cpp --- WinVoice test
// See ReadMe.txt and License.txt.
////////////////////////////////////////////////////////////////////////////

#include "WinVoice.hpp"

int main(void)
{
    CoInitialize(NULL);
    {
        WinVoice voice;
        voice.SetVolume(100);
        voice.Speak("How are you?", false);
        voice.Speak(L"I'm sick.", false);
        voice.Speak(L"\u3053\u3093\u306B\u3061\u308F\x3002", false);    // Japanese
    }
    CoUninitialize();
    return 0;
}

////////////////////////////////////////////////////////////////////////////
