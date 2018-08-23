#ifndef INCUBATION_H
#define INCUBATION_H


class Incubation : public QObject
{
    Q_OBJECT
public:
    explicit Incubation(QObject *parent = 0);
    void startIncub(int time_sec, int num);
    void stopIncub();
    bool isIncub();

signals:

public slots:
    void incubeTimeout();
};

#endif // INCUBATION_H
