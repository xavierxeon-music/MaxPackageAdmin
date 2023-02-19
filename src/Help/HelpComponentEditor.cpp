#include "HelpComponentEditor.h"

#include "HelpPersona.h"

#include <QHBoxLayout>
#include <QLabel>

Help::ComponentEditor::ComponentEditor(Persona* persona)
   : QWidget(persona)
   , persona(persona)
{
   QLabel* label = new QLabel("TO BE DONE", this);
   label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);

   QHBoxLayout* masterLayout = new QHBoxLayout(this);
   masterLayout->addWidget(label);
}
