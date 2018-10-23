// WinVoice.h --- SAPI wrapper module
// See ReadMe.txt and License.txt.
////////////////////////////////////////////////////////////////////////////

#ifndef WIN_VOICE_HPP_
#define WIN_VOICE_HPP_

#undef INITGUID
#define INITGUID

#include <string>
#include <windows.h>
#include <sapi.h>

////////////////////////////////////////////////////////////////////////////

// TODO: Please call CoInitialize[Ex] before usage.
class WinVoice
{
public:
    WinVoice()
    {
        HRESULT hr = ::CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_INPROC_SERVER,
                                        IID_ISpVoice, (void **)&m_pSpVoice);
        m_available = SUCCEEDED(hr);
        if (m_available)
        {
            hr = m_pSpVoice->SetOutput(NULL, TRUE);
            hr = m_pSpVoice->SetVolume(100);
            hr = hr;
        }
        m_mute = false;
    }
    void Copy(const WinVoice& voice)
    {
        m_available = voice.m_available;
        m_pSpVoice = voice.m_pSpVoice;
        m_mute = voice.m_mute;
        m_pSpVoice->AddRef();
    }
    WinVoice(const WinVoice& voice)
    {
        Copy(voice);
    }
    WinVoice& operator=(const WinVoice& voice)
    {
        Copy(voice);
        return *this;
    }
    virtual ~WinVoice()
    {
        m_pSpVoice->Release();
    }
    ISpVoice *SpVoice()
    {
        return m_pSpVoice;
    }
    HRESULT Speak(const std::wstring& str, bool async = true)
    {
        if (m_mute)
        {
            return 0;
        }
        DWORD flags = SPF_PURGEBEFORESPEAK;
        if (async)
        {
            flags |= SPF_ASYNC;
        }
        return m_pSpVoice->Speak(str.c_str(), flags, NULL);
    }
    HRESULT Speak(const std::string& str, bool async = true)
    {
        std::wstring wide;
        int len = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1,
                                        NULL, 0);
        wide.resize(len);
        ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1,
                              &wide[0], len);
        return Speak(wide, async);
    }
    bool IsAvailable() const { return this && m_available; }
    HRESULT GetVolume(USHORT *volume) { return m_pSpVoice->GetVolume(volume); }
    HRESULT SetVolume(USHORT volume) { return m_pSpVoice->SetVolume(volume); }
    HRESULT Pause() { return m_pSpVoice->Pause(); }
    HRESULT Resume() { return m_pSpVoice->Resume(); }
    HRESULT WaitUntilDone(ULONG msec) { return m_pSpVoice->WaitUntilDone(msec); }
    HRESULT GetRate(LONG *rate) { return m_pSpVoice->GetRate(rate); }
    HRESULT SetRate(LONG rate) { return m_pSpVoice->SetRate(rate); }
    void SetMute(BOOL on)
    {
        if (on)
        {
            m_pSpVoice->Speak(L"", SPF_PURGEBEFORESPEAK, NULL);
        }
        m_mute = !!on;
    }
    bool IsMute() const { return m_mute; }

protected:
    bool m_available;
    ISpVoice *m_pSpVoice;
    bool m_mute;
}; // class WinVoice

////////////////////////////////////////////////////////////////////////////

#endif  // ndef WIN_VOICE_HPP_
