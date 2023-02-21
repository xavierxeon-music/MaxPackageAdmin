#include "HelpComponentsModel.h"

#include <ModelItem.h>

Help::ComponentsModel::ComponentsModel(Persona* persona)
   : QStandardItemModel(persona)
   , Persona::FunctionHub()
   , persona(persona)
{
}

void Help::ComponentsModel::patchSelected(QString patchPath, QString key)
{
   Q_UNUSED(patchPath)

   clear();

   const PatchStructure* structure = persona->patchStructureRef(key);

   auto addMarker = [](const PatchStructure::Marker& marker, const QVariant& data, ModelItem* item1, ModelItem* item2)
   {
      item1->setData(QVariant::fromValue(marker), PatchStructure::RoleMarker);
      item1->setData(data, PatchStructure::RoleData);

      item2->setData(QVariant::fromValue(marker), PatchStructure::RoleMarker);
      item2->setData(data, PatchStructure::RoleData);
   };

   {
      ModelItem* patchItem = new ModelItem("PATCH");
      ModelItem* patchDigestItem = new ModelItem(structure->patchDigest.text);

      invisibleRootItem()->appendRow({patchItem, patchDigestItem});
      addMarker(PatchStructure::Marker::Patch, true, patchItem, patchDigestItem);
   }

   {
      ModelItem* argumentListItem = new ModelItem("ARGUMENTS");
      invisibleRootItem()->appendRow(argumentListItem);
      for (int index = 0; index < structure->argumentList.count(); index++)
      {
         const PatchStructure::Argument& argument = structure->argumentList.at(index);

         ModelItem* argItem = new ModelItem(argument.name);
         ModelItem* argDigestItem = new ModelItem(argument.digest.text);

         argumentListItem->appendRow({argItem, argDigestItem});
         addMarker(PatchStructure::Marker::Argument, index, argItem, argDigestItem);
      }
   }

   {
      ModelItem* attributeListItem = new ModelItem("ATTRIBUTES");
      invisibleRootItem()->appendRow(attributeListItem);
      for (PatchStructure::Attribute::Map::ConstIterator it = structure->attributeMap.constBegin(); it != structure->attributeMap.constEnd(); it++)
      {
         ModelItem* attrItem = new ModelItem(it.key());
         ModelItem* attrrDigestItem = new ModelItem(it.value().digest.text);

         attributeListItem->appendRow({attrItem, attrrDigestItem});
         addMarker(PatchStructure::Marker::Attribute, it.key(), attrItem, attrrDigestItem);
      }
   }

   {
      ModelItem* messageListItem = new ModelItem("MESSAGES");
      invisibleRootItem()->appendRow(messageListItem);
      for (PatchStructure::Message::Map::ConstIterator it = structure->messageMap.constBegin(); it != structure->messageMap.constEnd(); it++)
      {
         ModelItem* msgItem = new ModelItem(it.key());
         ModelItem* msgDigestItem = new ModelItem(it.value().digest.text);

         messageListItem->appendRow({msgItem, msgDigestItem});
         addMarker(PatchStructure::Marker::Message, true, msgDigestItem, msgDigestItem);
      }
   }

   {
      ModelItem* outputListItem = new ModelItem("OUTPUTS");
      invisibleRootItem()->appendRow(outputListItem);
      for (PatchStructure::Output::Map::ConstIterator it = structure->outputMap.constBegin(); it != structure->outputMap.constEnd(); it++)
      {
         ModelItem* outputItem = new ModelItem(QString::number(it.key()));
         ModelItem* outputDigestItem = new ModelItem(it.value().name);

         outputListItem->appendRow({outputItem, outputDigestItem});
         addMarker(PatchStructure::Marker::Output, it.key(), outputItem, outputDigestItem);
      }
   }
}
