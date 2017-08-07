#ifndef LIST_OBJECT3D_H
#define LIST_OBJECT3D_H

#include <QWidget>
#include <object_viewer/scene3d/scene_3d.h>
#include <QTreeWidget>
#include <QTreeWidgetItem>

class ListObject3d : public QWidget
{
    Q_OBJECT
public:
    explicit ListObject3d(QWidget *parent = nullptr);
    ~ListObject3d();
public:

    QObject *forEventFilter();

private:

    QTreeWidget             __treeObjects;

    QList<Object3D>         __objects;
    QList<QTreeWidgetItem*> __items;

signals:

public slots:

    ///
    /// \brief Добавлен объект на сцену
    /// \param obj объект
    ///
    void AddedObject3d( Object3D obj );

    ///
    /// \brief Удален объект с сцены
    /// \param obj объект
    ///
    void RemovedObject3d( Object3D obj );
};

#endif // LIST_OBJECT3D_H
