#include "list_object3d.h"
#include <QLayout>

ListObject3d::ListObject3d(QWidget *parent) : QWidget(parent)
{
    auto *lay = new QVBoxLayout;
    lay->addWidget ( &__treeObjects );
    lay->setMargin ( 0 );

    this->setLayout ( lay );
}

ListObject3d::~ListObject3d()
{

}

QObject *ListObject3d::forEventFilter()
{
    return &__treeObjects;
}

void ListObject3d::AddedObject3d(Object3D obj)
{
    auto *item = new QTreeWidgetItem();
    item->setText ( 0, obj.get ()->name () );

    __treeObjects.addTopLevelItem ( item );
    __objects << obj;
    __items << item;

}

void ListObject3d::RemovedObject3d(Object3D obj)
{
    int pos = __objects.indexOf ( obj );

    if ( pos  != -1 ) {

        __objects.removeAt ( pos );

        auto *item = __items.at ( pos );
        __items.removeAt ( pos );
        delete item;
    }
 }
