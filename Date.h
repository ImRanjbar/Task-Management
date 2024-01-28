#ifndef DATE_H
#define DATE_H

class Date
{
public:
    Date();
    Date(int day, int month, int year);

    void setDay(int day);
    void setMonth(int month);
    void setYear(int year);

    int getDay() const;
    int getMonth() const;
    int getYear() const;

    bool isValidDate() const;

    bool operator==(const Date& other) const;
    bool operator<(const Date& other) const;
    bool operator>(const Date& other) const;

private:
    int m_day;
    int m_month;
    int m_year;

};

#endif // DATE_H
