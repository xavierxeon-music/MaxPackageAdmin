#include "HelpComponentsModel.h"

#include <ModelItem.h>

Help::ComponentsModel::ComponentsModel(Persona* persona)
   : QStandardItemModel(persona)
   , Persona::FunctionHub()
   , persona(persona)
{
}

void Help::ComponentsModel::patchSelected(QString patchPath)
{
   Q_UNUSED(patchPath)

   clear();

   const PatchStructure* structure = persona->patchStructureRef();

   auto addMarker = [](ModelItem* item, const PatchStructure::Marker& marker, const QVariant& data)
   {
      item->setData(QVariant::fromValue(marker), PatchStructure::RoleMarker);
      item->setData(data, PatchStructure::RoleData);
   };

   {
      ModelItem* patchItem = new ModelItem("PATCH");
      addMarker(patchItem, PatchStructure::Marker::Patch, true);

      ModelItem* patchDigestItem = new ModelItem(structure->patchDigest.text);

      invisibleRootItem()->appendRow({patchItem, patchDigestItem});
   }

   {
      ModelItem* argumentListItem = new ModelItem("ARGUMENTS");
      invisibleRootItem()->appendRow(argumentListItem);
      for (int index = 0; index < structure->argumentList.count(); index++)
      {
         const PatchStructure::Argument& argument = structure->argumentList.at(index);

         ModelItem* argItem = new ModelItem(argument.name);
         addMarker(argItem, PatchStructure::Marker::Argument, index);

         ModelItem* argDigestItem = new ModelItem(argument.digest.text);

         argumentListItem->appendRow({argItem, argDigestItem});
      }
   }

   {
      ModelItem* attributeListItem = new ModelItem("ATTRIBUTES");
      invisibleRootItem()->appendRow(attributeListItem);
      for (PatchStructure::Attribute::Map::ConstIterator it = structure->attributeMap.constBegin(); it != structure->attributeMap.constEnd(); it++)
      {
         ModelItem* attrItem = new ModelItem(it.key());
         addMarker(attrItem, PatchStructure::Marker::Attribute, it.key());

         ModelItem* attrrDigestItem = new ModelItem(it.value().digest.text);

         attributeListItem->appendRow({attrItem, attrrDigestItem});
      }
   }

   {
      ModelItem* messageListItem = new ModelItem("MESSAGES");
      invisibleRootItem()->appendRow(messageListItem);
      for (PatchStructure::Message::Map::ConstIterator it = structure->messageMap.constBegin(); it != structure->messageMap.constEnd(); it++)
      {
         ModelItem* msgItem = new ModelItem(it.key());
         addMarker(msgItem, PatchStructure::Marker::Message, it.key());

         ModelItem* msgDigestItem = new ModelItem(it.value().digest.text);

         messageListItem->appendRow({msgItem, msgDigestItem});
      }
   }

   {
      ModelItem* outputListItem = new ModelItem("OUTPUTS");
      invisibleRootItem()->appendRow(outputListItem);
      for (PatchStructure::Output::Map::ConstIterator it = structure->outputMap.constBegin(); it != structure->outputMap.constEnd(); it++)
      {
         ModelItem* outputItem = new ModelItem(QString::number(it.key()));
         addMarker(outputItem, PatchStructure::Marker::Output, it.key());

         ModelItem* outputDigestItem = new ModelItem(it.value().name);

         outputListItem->appendRow({outputItem, outputDigestItem});
      }
   }
}
