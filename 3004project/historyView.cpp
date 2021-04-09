#include "historyView.h"

/**
 * @brief Constructs the name of the history treatment.
 * @return the data of the history view.
 */
QString HistoryView::getName() {
    QString weekday = previousTreatment->date.toString();
    QString time = previousTreatment->time.toString();
    QString type = previousTreatment->therapy->getType();
    QString powerLevel = QString::number(previousTreatment->getMaxPowerLevel());
    QString minutes = QString::number(floor(previousTreatment->getDurationInSeconds() / 60));
    QString seconds = QString::number(previousTreatment->getDurationInSeconds() % 60);

    return QString("%1 %2\nTreatment: %3, %4\nPower Level: %5\nDuration: %6m%7s")
            .arg(weekday, time, type, name, powerLevel, minutes, seconds);
}
