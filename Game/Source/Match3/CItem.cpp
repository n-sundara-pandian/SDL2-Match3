
#include <Match3/CItem.h>
#include <Utils/Common.h>

CItem::CItem(Color color) 
  : m_color(color)
  , m_state(State::Clean)
{
}


void CItem::Update(float dt)
{
}


void CItem::ChangeColor()
{
  m_color = Utils::GetRandomColor();
}

