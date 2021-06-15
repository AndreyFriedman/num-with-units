#ifndef NUMBERWITHUNITS_
#define NUMBERWITHUNITS_
#include <iostream>
#include <string>
#include <unordered_map>
#include <exception>
namespace ariel
{
    typedef struct unit{
        std::string s;
        double value;
    } unit;
    class NumberWithUnits{
        private:

        double value;
        std::string unit;
        bool checkKey(std::string key) const;
        NumberWithUnits convert (std::string u1,std::string u2, double v) const;
        bool way(std::string t1, std::string t2) const;
        static std::unordered_map<std::string,ariel::unit> map;
        
        public:

        NumberWithUnits(){}

        NumberWithUnits(const NumberWithUnits & other){
            this->value =other.value;
            this->unit =other.unit;
        }
        NumberWithUnits(double value,std::string unit){
            if(unit == "")
                throw std::invalid_argument("");
            if (checkKey(unit)){
                this->value = value;
                this->unit = unit;
            }
            else
                throw std::invalid_argument("");
        }
        static void read_units(std::ifstream & stream);
        NumberWithUnits operator+ (const NumberWithUnits &other)const;
        NumberWithUnits operator+= (const NumberWithUnits& other);
        NumberWithUnits operator+ ()const;
        NumberWithUnits operator- (const NumberWithUnits &other)const;
        NumberWithUnits operator-= (const NumberWithUnits& other);
        NumberWithUnits operator- ()const;
        NumberWithUnits & operator++ ();
        NumberWithUnits operator++( int dummy);
        NumberWithUnits & operator-- ();
        NumberWithUnits operator-- (int dummy);    

        bool operator< (const NumberWithUnits & other)const;
        bool operator<= (const NumberWithUnits & other)const;
        bool operator> (const NumberWithUnits & other)const;
        bool operator>= (const NumberWithUnits & other)const;
        bool operator== (const NumberWithUnits & other)const;
        bool operator!= (const NumberWithUnits & other)const;

        friend std::ostream & operator<< (std::ostream & os, const NumberWithUnits & other);
        friend std::istream & operator>> (std::istream & is, NumberWithUnits & other);
        friend NumberWithUnits operator* (double bap,const NumberWithUnits & n);
        NumberWithUnits operator* ( double  v);

        std::string getunit()const{
            return unit;
        }
        double getvalue()const{
            return value;
        }
        void setvalue(double value){
            this->value = value;
        }
    };
}
#endif