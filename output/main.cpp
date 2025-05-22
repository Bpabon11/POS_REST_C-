#include <wx/wx.h>

class MyApp : public wxApp {
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame {
public:
    MyFrame();
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
    MyFrame* frame = new MyFrame();
    frame->Show(true);
    return true;
}

MyFrame::MyFrame()
    : wxFrame(nullptr, wxID_ANY, "Sistema de Gestión de Restaurante", wxDefaultPosition, wxSize(600, 400)) {

    new wxButton(this, wxID_ANY, "Tomar pedido", wxPoint(200, 150), wxSize(200, 50));
}