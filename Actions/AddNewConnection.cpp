#include "AddNewConnection.h"

#include "../ApplicationManager.h"
#include "../Components/Connection.h"
#include "../Components/InputPin.h"
#include "../Components/OutputPin.h"

AddNewConnection::AddNewConnection(ApplicationManager *pApp): Action(pApp) {}

void AddNewConnection::ReadActionParameters()
{
    m_InputPin = pManager->GetPinAt(pManager->GetInterface()->GetMousePosition());
    if (m_InputPin == NULL)
        return;
    std::pair<int,int> Point;
    do
    {
        pManager->UpdateInterface();
        pManager->GetInterface()->PrintMsg("Click another pin");
        pManager->SyncInterface();
        Point = pManager->GetInterface()->GetInstantClick();
    } while (Point.first == -1 && Point.second == -1);
    m_OutputPin = pManager->GetPinAt(Point);
    if (m_OutputPin == NULL)
        return;
    OutputPin* CheckInputPin = dynamic_cast<OutputPin*> (m_InputPin);
    InputPin* CheckOutputPin = dynamic_cast<InputPin*> (m_OutputPin);
    if (CheckInputPin == NULL && CheckOutputPin == NULL)
        std::swap(m_InputPin, m_OutputPin);
    else if (CheckInputPin == NULL || CheckOutputPin == NULL)
        m_InputPin = m_OutputPin = NULL;
}

void AddNewConnection::Execute()
{
    ReadActionParameters();
    if (m_InputPin == NULL || m_OutputPin == NULL || !m_InputPin->IsConnectable() || !m_OutputPin->IsConnectable())
        return;
    pConnection = new Connection(m_InputPin, m_OutputPin, pManager->FindPathThroughGrid(m_InputPin->GetCenter(), m_OutputPin->GetCenter()));
	pManager->AddComponent(pConnection);
	pManager->AddCompletedAction(new AddNewConnection(*this));
}

void AddNewConnection::Undo()
{
    pManager->RemoveComponent(pConnection);
}

void AddNewConnection::Redo()
{
    pManager->AddComponent(pConnection);
}
