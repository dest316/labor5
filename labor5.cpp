#include<iostream>
#include<fstream>
#include<string>
using namespace std;

struct scan_info
{
    string model;
    int price;
    double x_size;
    double y_size;
    int optr;
    int grey;

    friend std::ostream& operator<< (std::ostream& out, const scan_info& scaninfo);

    bool operator ==(const scan_info& other)
    {
        if (this->model == other.model)
        {
            return true;
        }
        return false;
    }
};

ostream& operator<< (std::ostream& out, const scan_info& scaninfo)
{
    out << scaninfo.model << " " << scaninfo.price << " " << scaninfo.x_size << " " << scaninfo.y_size << " " << scaninfo.optr << " " << scaninfo.grey << endl;
    return out;
}

class ScanFile
{
private:
    string path;
    fstream fs;
public:  
    static int RecordsCount; //количество записей
    /*static void setRecordsCount(int count)
    {
        ScanFile::RecordsCount = count;
    } */
    ScanFile(string path_to_file)
    {
        //fstream fs;
        this->path = path_to_file;
        fs.open(path, fstream::in | fstream::out | fstream::ate | fstream::binary);
        if (!fs.is_open())
        {
            cout << "Ошибка: не удалось открыть файл!" << endl;
            exit(1);
        }
    }
    ~ScanFile()
    {
        fs.close();
    }
    void writeStruct(scan_info record)
    {
        
        
        try
        {
            fs.seekg(0, ios::beg);
            RecordsCount++;
            fs << RecordsCount << endl;
            fs.seekg(0, ios::end);
            fs << record;
        }
        catch (const std::exception& ex)
        {
            cout << "Что-то пошло не так, скорее всего произошла проблема при работе с файлом" << endl;
            cout << "Error: " << ex.what() << endl;
        }
        
        
    }
    scan_info createStruct()
    {
        scan_info si;
        cout << "Введите параметры сканера..." << endl;
        cin >> si.model >> si.price >> si.x_size >> si.y_size >> si.optr >> si.grey;
        if (cin.fail())
        {
            si.model = "<undefined>";
            si.price = si.x_size = si.y_size = si.optr = si.grey = 0;
        }
        return si;
    }
    void check_count_records_in_file()
    {
        if (fs.tellg() != 0)
        {
            fs.seekg(0, ios::beg);
            try
            {
                string temp;
                getline(fs, temp);
                RecordsCount += stoi(temp);
            }
            catch (const std::exception& ex)
            {
                cout << "Что-то пошло не так, скорее всего файл имеет неправильную структуру, либо не открыт" << endl;
                cout << "Error: " << ex.what() << endl;

            }
        }
    }
    bool foundstruct(scan_info addedscan)
    {
        string temp;
        fs.seekg(0, ios::beg);
        for (int i = 0; i < RecordsCount; i++)
        {
            string temp1 = "";
            getline(fs, temp);
            for (int i = 0; i < temp.size(); i++)
            {
                if (temp[i] == ' ')
                {
                    break;
                }
                temp1 += temp[i];
            }
            if (temp1 == addedscan.model)
            {
                return true;
            }
        }
        return false;
    }
    void try_add_struct()
    {
        scan_info temp = createStruct();
        if (temp.model != "<undefined>")
        {
            if (foundstruct(temp))
            {
                cout << "Информация о данной модели сканера уже есть в файле" << endl;
            }
            else
            {
                writeStruct(temp);
                cout << "Информация успешно записана" << endl;
            }
        }
        else
        {
            cout << "При создании структура возникла ошибка: какое-то из полей введено некорректно" << endl;

        }
    }
};

int ScanFile::RecordsCount = 0;

int main()
{
    setlocale(LC_ALL, "ru");
    string path = "mainfile";
    ScanFile mainfile(path);
    mainfile.check_count_records_in_file();
    cout << "Введите количество структур, которые вы хотите записать в файл..." << endl;
    int n;
    cin >> n;
    if (!cin.fail())
    {
        for (size_t i = 0; i < n; i++)
        {
            mainfile.try_add_struct();
        }
    }
    else
    {
        cout << "Некорретно введено количество структур (подсказка: используйте целые числа)" << endl;
    }
    return 0;
}
