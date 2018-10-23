// WinVoiceTest.cpp --- WinVoice test
// Copyright (C) 2018 Katayama Hirofumi MZ <katayama.hirofumi.mz@gmail.com>
// This file is public domain software.
////////////////////////////////////////////////////////////////////////////

#include "WinVoice.hpp"
#include "resource.h"

int main(void)
{
    CoInitialize(NULL);
    {
        WinVoice voice;
        voice.SetVolume(100);
        voice.Speak("How are you?", false);
        voice.Speak(L"I'm sick.", false);
        voice.Speak(IDS_KONNICHIWA, false);    // Japanese resource
    }
    CoUninitialize();
    return 0;
}

////////////////////////////////////////////////////////////////////////////
