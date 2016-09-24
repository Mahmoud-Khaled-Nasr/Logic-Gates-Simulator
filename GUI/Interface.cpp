#include "Interface.h"

#include "Bar.h"
#include "Button.h"
#include "Canvas.h"
#include "Input.h"
#include "Output.h"

Interface::Interface(int r_X, int r_Y): Window(sf::VideoMode::getDesktopMode(), "Logic Simulator", sf::Style::Fullscreen)
{
    Window.setFramerateLimit(0);
    WindowWidth = Window.getSize().x;
    WindowHeight = Window.getSize().y;
    Spacing = 5;
    BorderSize = 6;
    StatusBarHeight = 22;
    GatesBarHeight = 130;
    ToolBarWidth = 60;
    GateSide = 60;
    m_Busy = false;
	Themes.push_back("RIVER/");
	Themes.push_back("TURQUOISE/");
	Themes.push_back("EMERALD/");
	Themes.push_back("AMETHYST/");
	Themes.push_back("SUNFLOWER/");
	AppTheme = -1;
	SwitchAppTheme();
	AppMode = DESIGN;
    GridSize = 10;
    PinRadius = 4;

    SizeX = r_X;
    SizeY = r_Y;
	Zoom = 2;
	Offset.first = 0;
	Offset.second = 0;

    MainInput = new Input(this),
    MainOutput = new Output(this),
    StatusBar = new Bar(GraphicsInfo(0, WindowHeight-StatusBarHeight, WindowWidth, StatusBarHeight), Bar::HORIZONTAL, 0);
    DesignBar = new Bar(GraphicsInfo(0, 0, ToolBarWidth, WindowHeight-StatusBarHeight-BorderSize), Bar::VERTICAL, Spacing);
    SimulationBar = new Bar(GraphicsInfo(0, 0, ToolBarWidth, WindowHeight-StatusBarHeight-BorderSize), Bar::VERTICAL, Spacing);
    GatesBar = new Bar(GraphicsInfo(ToolBarWidth+BorderSize, 0, WindowWidth-ToolBarWidth-BorderSize, GatesBarHeight), Bar::HORIZONTAL, Spacing);
    NGatesBar = new Bar(GraphicsInfo(ToolBarWidth+BorderSize, GatesBarHeight, WindowWidth-ToolBarWidth-BorderSize, GatesBarHeight), Bar::HORIZONTAL, Spacing);
    SimCanvas = new Canvas(GraphicsInfo(ToolBarWidth+BorderSize, 0, WindowWidth-ToolBarWidth-BorderSize, WindowHeight-StatusBarHeight-BorderSize));
    DesignBar->AddButton("add", ADD);
    DesignBar->AddButton("delete", DELETE, Interface::DISABLED);
    DesignBar->AddButton("copy", COPY, Interface::DISABLED);
    DesignBar->AddButton("cut", CUT, Interface::DISABLED);
    DesignBar->AddButton("undo", UNDO, Interface::DISABLED);
    DesignBar->AddButton("redo", REDO, Interface::DISABLED);
    DesignBar->AddButton("save", SAVE);
    DesignBar->AddButton("load", LOAD);
    DesignBar->AddButton("simulate", SIMULATE);
    DesignBar->AddButton("color", SWITCH_THEME);
    DesignBar->AddButton("exit", EXIT);
    SimulationBar->AddButton("table", CREATE_TRUTHTABLE);
    SimulationBar->AddButton("stop", STOP, Interface::NORMAL, 7);
    SimulationBar->AddButton("color", SWITCH_THEME);
    SimulationBar->AddButton("exit", EXIT);
    GatesBar->AddButton("BUFFER", ADD_BUFF);
    NGatesBar->AddButton("NOT", ADD_INV);
    GatesBar->AddButton("AND2", ADD_AND_GATE_2);
    NGatesBar->AddButton("NAND2", ADD_NAND_GATE_2);
    GatesBar->AddButton("OR2", ADD_OR_GATE_2);
    NGatesBar->AddButton("NOR2", ADD_NOR_GATE_2);
    GatesBar->AddButton("XOR2", ADD_XOR_GATE_2);
    NGatesBar->AddButton("XNOR2", ADD_XNOR_GATE_2);
    GatesBar->AddButton("AND3", ADD_AND_GATE_3);
    NGatesBar->AddButton("NAND3", ADD_NAND_GATE_3);
    GatesBar->AddButton("OR3", ADD_OR_GATE_3);
    NGatesBar->AddButton("NOR3", ADD_NOR_GATE_3);
    GatesBar->AddButton("XOR3", ADD_XOR_GATE_3);
    NGatesBar->AddButton("XNOR3", ADD_XNOR_GATE_3);
    GatesBar->AddButton("SWITCH", ADD_SWITCH);
    NGatesBar->AddButton("LED", ADD_LED);
    DesignBar->OptimizeSpacing();
    SimulationBar->OptimizeSpacing();
    GatesBar->OptimizeSpacing();
    NGatesBar->OptimizeSpacing();
    Window.setMouseCursorVisible(false);
    ClearCanvas();
    ResetWindow();
    SyncWindow();
}

Interface::~Interface()
{
    delete MainInput;
    delete MainOutput;
    delete StatusBar;
    delete DesignBar;
    delete SimulationBar;
    delete GatesBar;
    delete NGatesBar;
    delete SimCanvas;
}

void Interface::SetBusy(bool r_Busy)
{
    m_Busy = r_Busy;
}

void Interface::SetMouseStatus(MouseStatus r_MouseStatus)
{
    MainOutput->SetMouseStatus(r_MouseStatus);
}

std::vector<Button*> Interface::GetActiveButtons()
{
    return GetActiveBar()->GetButtons();
}

std::vector<Button*> Interface::GetGatesButtons()
{
    std::vector<Button*> Buttons;
    Buttons.reserve( GatesBar->GetButtons().size() + NGatesBar->GetButtons().size() );
    Buttons.insert( Buttons.end(), GatesBar->GetButtons().begin(), GatesBar->GetButtons().end() );
    Buttons.insert( Buttons.end(), NGatesBar->GetButtons().begin(), NGatesBar->GetButtons().end() );
    return Buttons;
}

void Interface::DrawGatesBars()
{
    GatesBar->Draw(MainOutput);
    NGatesBar->Draw(MainOutput);
}

void Interface::EnableButtonWithAction(ActionType ActType)
{
    const std::vector<Button*>& dummyVector = GetActiveBar()->GetButtons();
    for(unsigned int j = 0; j < dummyVector.size(); j++)
        if (dummyVector[j] != NULL && dummyVector[j]->GetAction() == ActType)
        {
            dummyVector[j]->SetStatus(Interface::NORMAL);
            break;
        }
}

void Interface::DisableButtonWithAction(ActionType ActType)
{
    const std::vector<Button*>& dummyVector = GetActiveBar()->GetButtons();
    for(unsigned int j = 0; j < dummyVector.size(); j++)
        if (dummyVector[j] != NULL && dummyVector[j]->GetAction() == ActType)
        {
            dummyVector[j]->SetStatus(Interface::DISABLED);
            break;
        }
}

bool Interface::IsSimulating() const
{
    return AppMode == SIMULATION;
}

void Interface::SwitchAppMode()
{
    AppMode = (AppMode==DESIGN) ? SIMULATION : DESIGN;
}

void Interface::SwitchAppTheme()
{
    AppTheme = (AppTheme+1)%Themes.size();
    BackgroundColor = sf::Color::White;
    switch (AppTheme)
    {
    case 0:
        AlphaColor = sf::Color(0x29, 0x80, 0xb9);
        BetaColor = sf::Color(0x34, 0x98, 0xdb);
        SelectionColor = sf::Color(0x34, 0x98, 0xdb, 0x33);
        GridColor = sf::Color(0x34, 0x98, 0xdb, 0x26);
        break;
    case 1:
        AlphaColor = sf::Color(0x16, 0xa0, 0x85);
        BetaColor = sf::Color(0x1a, 0xbc, 0x9c);
        SelectionColor = sf::Color(0x1a, 0xbc, 0x9c, 0x33);
        GridColor = sf::Color(0x1a, 0xbc, 0x9c, 0x26);
        break;
    case 2:
        AlphaColor = sf::Color(0x27, 0xae, 0x60);
        BetaColor = sf::Color(0x2e, 0xcc, 0x71);
        SelectionColor = sf::Color(0x2e, 0xcc, 0x71, 0x33);
        GridColor = sf::Color(0x2e, 0xcc, 0x71, 0x26);
        break;
    case 3:
        AlphaColor = sf::Color(0x8e, 0x44, 0xad);
        BetaColor = sf::Color(0x9b, 0x59, 0xb6);
        SelectionColor = sf::Color(0x9b, 0x59, 0xb6, 0x33);
        GridColor = sf::Color(0x9b, 0x59, 0xb6, 0x26);
        break;
    case 4:
        AlphaColor = sf::Color(0xf3, 0x9c, 0x12);
        BetaColor = sf::Color(0xf1, 0xc4, 0x0f);
        SelectionColor = sf::Color(0xf1, 0xc4, 0x0f, 0x33);
        GridColor = sf::Color(0xf1, 0xc4, 0x0f, 0x26);
        break;
    default:
        break;
    }
}

void Interface::ZoomIn()
{
    if (Zoom < 5)
    {
        std::pair<int,int> Center = MainInput->GetMousePosition();
        Offset.first = Offset.first + (Center.first-ToolBarWidth-BorderSize+Offset.first)/double(Zoom) + 0.5;
        Offset.second = Offset.second + (Center.second+Offset.second)/double(Zoom) + 0.5;
        Zoom++;
        GridSize = GridSize/(Zoom-1)*Zoom;
        PinRadius = PinRadius/(Zoom-1)*Zoom;
        ShiftOffsetBy(std::pair<int,int> (0, 0));
    }
}

void Interface::ZoomOut()
{
    if (Zoom > 2)
    {
        std::pair<int,int> Center = std::pair<int,int> (SimCanvas->GetGraphicsInfo().GetX()+SimCanvas->GetGraphicsInfo().GetWidth()/2.0+0.5, SimCanvas->GetGraphicsInfo().GetY()+SimCanvas->GetGraphicsInfo().GetHeight()/2.0+0.5);
        Offset.first = Offset.first - (Center.first-ToolBarWidth-BorderSize+Offset.first)/double(Zoom) + 0.5;
        Offset.second = Offset.second - (Center.second+Offset.second)/double(Zoom) + 0.5;
        Zoom--;
        GridSize = GridSize/(Zoom+1)*Zoom;
        PinRadius = PinRadius/(Zoom+1)*Zoom;
        ShiftOffsetBy(std::pair<int,int> (0, 0));
    }
}

void Interface::ShiftOffsetBy(std::pair<int,int> Delta)
{
    Offset.first = std::min(std::max(0, Offset.first+Delta.first), SizeX*Zoom*5 - SimCanvas->GetGraphicsInfo().GetX() - SimCanvas->GetGraphicsInfo().GetWidth()+ToolBarWidth+BorderSize);
    Offset.second = std::min(std::max(0, Offset.second+Delta.second), SizeY*Zoom*5 - SimCanvas->GetGraphicsInfo().GetY() - SimCanvas->GetGraphicsInfo().GetHeight());
}

void Interface::ClearCanvas()
{
    SimCanvas->Draw(MainOutput);
}

void Interface::ResetWindow()
{
    MainOutput->DrawBorders();
    GetActiveBar()->Draw(MainOutput);
    StatusBar->Draw(MainOutput);
}

void Interface::SyncWindow()
{
    MainOutput->SyncWindow();
}

void Interface::DrawComponent(const GraphicsInfo& GfxInfo, std::string ImagePath, ComponentStatus r_Status)
{
    MainOutput->DrawComponent(BufferGfxInfo(GfxInfo), std::string("")+ char(Zoom + '0') +"/"+ImagePath,r_Status);
}

void Interface::DrawLabel(const GraphicsInfo& GfxInfo, std::string Text)
{
    if (Text == "$")
        return;
    MainOutput->DrawLabel(BufferGfxInfo(GfxInfo), Text, "monof55");
}

void Interface::DrawPin(std::pair<int,int> Center, bool Connected, bool Connectable)
{
    MainOutput->DrawPin(BufferPoint(Center), Connected, Connectable, std::string("Components/")+char(Zoom + '0')+std::string("/PIN/"));
}

void Interface::DrawConnection(const std::vector< std::pair<int,int> >& Vertices, ComponentStatus r_Status, Signal r_Signal)
{
    std::vector< std::pair<int,int> > BufferedVertices;
    for(unsigned int i = 0; i < Vertices.size(); i++)
        BufferedVertices.push_back(BufferPoint(Vertices[i]));
    MainOutput->DrawConnection(BufferedVertices, r_Status, r_Signal);
}

void Interface::DrawSelectionRectangle(const GraphicsInfo& GfxInfo)
{
    MainOutput->DrawSelectionRectangle(BufferGfxInfo(GfxInfo));
}

void Interface::PrintMsg(std::string Text)
{
    StatusBar->Draw(MainOutput);
    MainOutput->DrawLabel(GraphicsInfo(StatusBar->GetGraphicsInfo()), Text, "CaviarDreams");
}

void Interface::SetTooltipText(std::string Text)
{
    MainOutput->SetTooltipText(Text);
}

std::pair<int,int> Interface::GetMousePosition(bool Absolute) const
{
    if (Absolute)
        return MainInput->GetMousePosition();
    return ReverseBufferPoint(MainInput->GetMousePosition());
}

std::pair<int,int> Interface::GetPointClicked(bool Absolute) const
{
    if (Absolute)
        return MainInput->GetPointClicked();
    return ReverseBufferPoint(MainInput->GetPointClicked());
}

std::pair<int,int> Interface::GetInstantClick(bool Absolute) const
{
    std::pair<int,int> dummy = MainInput->GetInstantClick();
    if (Absolute || (dummy.first == -1 && dummy.second == -1))
        return dummy;
    return ReverseBufferPoint(dummy);
}

std::pair<int,int> Interface::GetInstantRelease(bool Absolute) const
{
    std::pair<int,int> dummy = MainInput->GetInstantRelease();
    if (Absolute || (dummy.first == -1 && dummy.second == -1))
        return dummy;
    return ReverseBufferPoint(dummy);
}

std::string Interface::GetSrting() const
{
    return MainInput->GetSrting();
}

ActionType Interface::GetUserAction() const
{
    return MainInput->GetUserAction();
}

bool Interface::IsDoubleClick() const
{
    return MainInput->IsDoubleClick();
}

bool Interface::IsDragging() const
{
    return MainInput->IsDragging();
}

bool Interface::IsCtrlOn() const
{
    return MainInput->IsCtrlOn();
}

Bar* Interface::GetActiveBar()
{
    return (AppMode==DESIGN) ? DesignBar : SimulationBar;
}


std::pair<int,int> Interface::BufferPoint(std::pair<int,int> Point) const
{
    return std::pair<int,int> (ToolBarWidth+BorderSize+Point.first*Zoom*5-Offset.first, Point.second*Zoom*5-Offset.second);
}

std::pair<int,int> Interface::ReverseBufferPoint(std::pair<int,int> Point) const
{
    return std::pair<int,int> (double(Point.first-ToolBarWidth-BorderSize+Offset.first)/Zoom/5+0.5, double(Point.second+Offset.second)/Zoom/5+0.5);
}

GraphicsInfo Interface::BufferGfxInfo(GraphicsInfo GfxInfo) const
{
    return GraphicsInfo(BufferPoint(std::pair<int,int>(GfxInfo.GetX(), GfxInfo.GetY())), std::pair<int,int>(GfxInfo.GetWidth()*Zoom*5, GfxInfo.GetHeight()*Zoom*5));
}
