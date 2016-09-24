#include "Output.h"

Output::Output(Interface* pInterface)
{
    this->pInterface = pInterface;
    m_MouseStatus = Interface::POINTER;
}

void Output::DrawBar(const GraphicsInfo& GfxInfo)
{
    sf::RectangleShape Rectangle;
    Rectangle.setSize(sf::Vector2f(GfxInfo.GetWidth(), GfxInfo.GetHeight()));
    Rectangle.setPosition(GfxInfo.GetX(), GfxInfo.GetY());
    Rectangle.setFillColor(pInterface->BackgroundColor);
    pInterface->Window.draw(Rectangle);
}

void Output::DrawButton(const GraphicsInfo& GfxInfo, std::string ImagePath, Interface::ButtonStatus Status)
{
    ImagePath = "Buttons/" + ImagePath;
    DrawRectangle(GfxInfo, pInterface->BackgroundColor);
    switch (Status)
    {
    case Interface::NORMAL:
        {
            std::pair<int,int> Point = pInterface->GetMousePosition(true);
            if (GfxInfo.Contains(Point) && !(pInterface->m_Busy))
            {
                DrawImage(GfxInfo, ImagePath+"/2");
                SetTooltipText(ImagePath.substr(8));
                m_MouseStatus = Interface::CLICKER;
            }
            else
                DrawImage(GfxInfo, ImagePath+"/1");
        }
        break;
    case Interface::FOCUSED:
        {
            m_MouseStatus = Interface::CLICKER;
            std::pair<int,int> Point = pInterface->GetMousePosition(true);
            if (GfxInfo.Contains(Point))
            {
                DrawImage(GfxInfo, ImagePath+"/3");
                SetTooltipText(ImagePath.substr(8));
                m_MouseStatus = Interface::CLICKER;
            }
            else
                DrawImage(GfxInfo, ImagePath+"/1");
        }
        break;
    case Interface::PRESSED:
        {
            std::pair<int,int> Point = pInterface->GetMousePosition(true);
            if (GfxInfo.Contains(Point) && !(pInterface->m_Busy))
                m_MouseStatus = Interface::CLICKER;
        }
        DrawImage(GfxInfo, ImagePath+"/3");
        break;
    case Interface::DISABLED:
        DrawImage(GfxInfo, ImagePath+"/4");
        break;
    }
}

void Output::DrawCanvas(const GraphicsInfo& GfxInfo, bool ShowGrid)
{
    DrawRectangle(GfxInfo, pInterface->BackgroundColor);
    if (ShowGrid)
    {
        for(int i = GfxInfo.GetX()+pInterface->GridSize-pInterface->Offset.first%pInterface->GridSize; i < GfxInfo.GetX()+GfxInfo.GetWidth(); i+=pInterface->GridSize)
        {
            sf::Vertex line[] =
            {
                sf::Vertex(sf::Vector2f(i, GfxInfo.GetY()), pInterface->GridColor),
                sf::Vertex(sf::Vector2f(i, GfxInfo.GetY()+GfxInfo.GetHeight()), pInterface->GridColor)
            };
            pInterface->Window.draw(line, 2, sf::Lines);
        }
        for(int i = GfxInfo.GetY()+pInterface->GridSize-pInterface->Offset.second%pInterface->GridSize; i < GfxInfo.GetY()+GfxInfo.GetHeight(); i+=pInterface->GridSize)
        {
            sf::Vertex line[] =
            {
                sf::Vertex(sf::Vector2f(GfxInfo.GetX(), i), pInterface->GridColor),
                sf::Vertex(sf::Vector2f(GfxInfo.GetX()+GfxInfo.GetWidth(), i), pInterface->GridColor)
            };
            pInterface->Window.draw(line, 2, sf::Lines);
        }
    }
}

void Output::DrawComponent(const GraphicsInfo& GfxInfo, std::string ImagePath, ComponentStatus r_Status)
{
    switch(r_Status)
    {
    case NORMAL:
        DrawImage(GfxInfo, "Components/"+ImagePath+"/1");
        break;
    case SELECTED:
        DrawImage(GfxInfo, "Components/"+ImagePath+"/2");
        break;
    case INVALID:
        DrawImage(GfxInfo, "Components/"+ImagePath+"/3");
        break;
    case ON:
        DrawImage(GfxInfo, "Components/"+ImagePath+"/4");
        break;
    }
}

void Output::DrawLabel(const GraphicsInfo& GfxInfo, std::string Text, std::string Font)
{
    DrawRectangle(GfxInfo, pInterface->GridColor);
    if (GfxInfo.GetWidth()/GfxInfo.GetHeight() < (int)Text.size())
        Text = Text.substr(0, GfxInfo.GetWidth()/GfxInfo.GetHeight()) + "...";
    DrawText(GfxInfo, Text, Font);
}

void Output::DrawPin(std::pair<int,int> Center, bool Connected, bool Connectable, std::string ImagePath)
{
    std::pair<int,int> Point = pInterface->GetMousePosition(true);
    if (Connectable && Center.first+pInterface->PinRadius >= Point.first && Center.first-pInterface->PinRadius <= Point.first && Center.second+pInterface->PinRadius >= Point.second && Center.second-pInterface->PinRadius <= Point.second)
    {
        DrawImage(GraphicsInfo(Center.first-pInterface->PinRadius, Center.second-pInterface->PinRadius, pInterface->PinRadius*2, pInterface->PinRadius*2), ImagePath+"1");
        m_MouseStatus = Interface::CLICKER;
    }
    if (Connected)
    {
        DrawImage(GraphicsInfo(Center.first-pInterface->PinRadius, Center.second-pInterface->PinRadius, pInterface->PinRadius*2, pInterface->PinRadius*2), ImagePath+"2");
    }
}

void Output::DrawConnection(const std::vector< std::pair<int,int> >& Vertices, ComponentStatus r_Status, Signal r_Signal)
{
    int Thickness = (r_Status == SELECTED) ? pInterface->Zoom*2 : pInterface->Zoom;
    sf::Color Color;
    switch(r_Signal)
    {
    case FLOATING:
        Color = pInterface->AlphaColor;
        break;
    case LOW:
        Color = pInterface->AlphaColor;
        break;
    case HIGH:
        Color = sf::Color::Red;
        break;
    }
    for(unsigned int i = 1; i < Vertices.size(); i++)
    {
        if (Vertices[i].first == Vertices[i-1].first)
            DrawRectangle(GraphicsInfo(Vertices[i].first-Thickness/2, std::min(Vertices[i].second, Vertices[i-1].second)-Thickness/2, Thickness, std::max(Vertices[i].second, Vertices[i-1].second)-std::min(Vertices[i].second, Vertices[i-1].second)+Thickness), Color);
        else
            DrawRectangle(GraphicsInfo(std::min(Vertices[i].first, Vertices[i-1].first)-Thickness/2, Vertices[i].second-Thickness/2, std::max(Vertices[i].first, Vertices[i-1].first)-std::min(Vertices[i].first, Vertices[i-1].first)+Thickness, Thickness), Color);
    }
}

void Output::DrawSelectionRectangle(const GraphicsInfo& GfxInfo)
{
    DrawRectangle(GfxInfo, pInterface->SelectionColor, 1, pInterface->AlphaColor);
}

void Output::SetTooltipText(std::string Text)
{
    TooltipText = Text;
    if (Text == "")
        m_MouseStatus = Interface::POINTER;
}

void Output::SetMouseStatus(Interface::MouseStatus r_MouseStatus)
{
    m_MouseStatus = r_MouseStatus;
}

void Output::DrawBorders()
{
    DrawRectangle(GraphicsInfo(pInterface->ToolBarWidth, 0, pInterface->BorderSize, pInterface->Window.getSize().y-pInterface->StatusBarHeight), pInterface->AlphaColor);
    DrawRectangle(GraphicsInfo(0, pInterface->WindowHeight-pInterface->StatusBarHeight-pInterface->BorderSize, pInterface->Window.getSize().x, pInterface->BorderSize), pInterface->AlphaColor);
}

void Output::SyncWindow()
{
    HandleMouse();
    pInterface->Window.display();
}

void Output::DrawImage(const GraphicsInfo& GfxInfo, std::string ImagePath)
{
    sf::Texture Texture;
    Texture.loadFromFile("Graphics/Themes/"+pInterface->Themes[pInterface->AppTheme]+ImagePath+".png");
    sf::Sprite Sprite;
    Sprite.setTexture(Texture);
    Sprite.setPosition(GfxInfo.GetX(), GfxInfo.GetY());
    Sprite.setScale(GfxInfo.GetWidth()/Sprite.getGlobalBounds().width, GfxInfo.GetHeight()/Sprite.getGlobalBounds().height);
    pInterface->Window.draw(Sprite);
}

void Output::DrawRectangle(const GraphicsInfo& GfxInfo, sf::Color Color, int Thickness, sf::Color OutlineColor)
{
    sf::RectangleShape Rectangle;
    Rectangle.setSize(sf::Vector2f(GfxInfo.GetWidth(), GfxInfo.GetHeight()));
    Rectangle.setPosition(GfxInfo.GetX(), GfxInfo.GetY());
    Rectangle.setFillColor(Color);
    Rectangle.setOutlineThickness(Thickness);
    Rectangle.setOutlineColor(OutlineColor);
    pInterface->Window.draw(Rectangle);
}

void Output::DrawText(const GraphicsInfo& GfxInfo, std::string Text, std::string FontPath)
{
    sf::Font Font;
    Font.loadFromFile("Graphics/Fonts/"+FontPath+".ttf");
    sf::Text TextView(Text, Font, GfxInfo.GetHeight());
    TextView.setPosition(GfxInfo.GetX(), GfxInfo.GetY());
    TextView.setColor(pInterface->AlphaColor);
    pInterface->Window.draw(TextView);
}

void Output::DrawTooltip()
{
    std::pair<int,int> Point = pInterface->GetMousePosition(true);
    sf::Font Font;
    Font.loadFromFile("Graphics/Fonts/CaviarDreams_Italic.ttf");
    sf::Text TextView(TooltipText, Font, 20);
    TextView.setPosition(Point.first+10, Point.second+10);
    TextView.setColor(pInterface->AlphaColor);
    DrawRectangle(GraphicsInfo(TextView.getGlobalBounds().left-2, TextView.getGlobalBounds().top-2, TextView.getGlobalBounds().width+4, TextView.getGlobalBounds().height+4), sf::Color::White, 1, pInterface->AlphaColor);
    pInterface->Window.draw(TextView);
}

void Output::HandleMouse()
{
    if (TooltipText != "")
        DrawTooltip();
    std::pair<int,int> Position = pInterface->GetMousePosition(true);
    std::string Path = "Mouse/";
    switch(m_MouseStatus)
    {
    case Interface::POINTER:
        Path += "cursor";
        break;
    case Interface::CLICKER:
        Path += "clicker";
        Position.first -= 5;
        break;
    case Interface::NAVIGATION:
        Path += "navigation-1";
        Position.first -= 10;
        Position.second -= 10;
        break;
    case Interface::DRAG:
        Path += "drag";
        Position.first -= 10;
        Position.second -= 10;
        break;
    case Interface::TEXT:
        Path += "cursor-8";
        Position.first -= 10;
        Position.second -= 10;
        break;
    case Interface::HIDDEN:
        return;
    }
    DrawImage(GraphicsInfo(Position, std::pair<int,int> (20,20)), Path);
}
