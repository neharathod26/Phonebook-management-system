

#include<iostream>
#include<string>
using namespace std;

//contains all the details of a contact
class contact
{
public:
    contact* prev;
    string Name;
    string MobNo1;
    string MobNo2;
    int star;
    contact* next;
    //parametrized constructor of class contact
    contact(string name, string mno1, string mno2, int st)
    {
        next = NULL;
        Name = name;
        MobNo1 = mno1;
        MobNo2 = mno2;
        star = st;
        prev = NULL;
    }
};

//global members of contact class initialized as NULL
contact* head = NULL;    //to hold the address of 1st node/contact of phonebook
contact* tail = NULL;    //to hold the address of last node/contact of phonebook
contact* head1 = NULL;   //to hold the address of 1st node of block list
contact* tail1 = NULL;   //to hold the address of 1st node of block list
class phoneList
{
public:
    void createContact(string, string, string, int);         //to create new contact node 
    contact* searchContact(string, contact*, contact*);      //to create new contact node
    int totalContacts();                                     //to calculate total number of contacts
    void displayContact(contact*, contact*);                  //to display list of all contacts
    void displayFavContacts();                               //to display favourite contacts
    void updateContact();                                    //to edit details of a contact node
    contact* deleteContact(string);                          //to delete a contact node
    void deleteAllContacts();                                //to delete all the contacts from the phonebook
    void createBlockList(string);                            //to add a contact from phonebook to block list
    void addBackToContactList(string);                       //to add a contact from block list into phonebook
    contact* deleteFromBL(string);                           //to delete a contact from block list
};

void phoneList::createContact(string name, string No1, string No2, int choice)
{
    contact* newn = new contact(name, No1, No2, choice);    //creating new class node

    if ((head == NULL) && (tail == NULL))    //if list is empty
    {
        head = tail = newn;
        newn->prev = head;
        newn->next = tail;
    }

    else
    {
        newn->next = head;
        head->prev = newn;
        head = newn;
        tail->next = head;
        head->prev = tail;
    }
    cout << "........YOU HAVE SUCESSFULLY ADDED A CONTACT IN YOUR PHONEBOOK........" << endl << endl;
}

contact* phoneList::searchContact(string name, contact* top, contact* bottom)
{
    //if list is empty
    if ((top == NULL) && (bottom == NULL))
    {
        cout << "Your phonebook is empty !!" << endl;
        return NULL;
    }
    else
    {
        int flag = 0;
        contact* temp = top;   //temporary pointer to traverse the list initialized with the starting pointer
        do
        {
            if (temp->Name == name)  //if name is found in the list
            {
                return temp;
                flag = 1;
            }
            temp = temp->next;
        } while (temp != (bottom->next));

        if (flag == 0)
            return NULL;
    }
}

int phoneList::totalContacts()
{
    int icnt = 0;
    //if list is empty
    if ((head == NULL) && (tail == NULL))
    {
        cout << "PHONEBOOK IS EMPTY !!" << endl;
        return -1;
    }

    contact* temp = head;  //temporary pointer to traverse the list initialized to head
    do
    {
        icnt++;
        temp = temp->next;
    } while (temp != (tail->next));
    return icnt;
}

void phoneList::displayContact(contact* top, contact* bottom)
{
    int i = 1;
    //if list is empty
    if ((top == NULL) && (bottom == NULL))
    {
        cout << "PHONEBOOK IS EMPTY" << endl;
        return;
    }

    contact* temp = top;   //temporary pointer to traverse the list initialized with starting pointer
    do
    {
        //displaying the details of each contact
        cout << "CONTACT " << i << " :" << endl;
        cout << "---------" << endl;
        cout << "Name     : " << temp->Name << endl;
        cout << "Number 1 : " << temp->MobNo1 << endl;
        if (temp->MobNo2 == "")
            cout << "Number 2 : Not added " << endl << endl;
        else
            cout << "Number 2 : " << temp->MobNo2 << endl << endl;
        temp = temp->next;
        i++;
    } while (temp != (bottom->next));
}

void phoneList::displayFavContacts()
{
    int i = 1;
    //if list is empty
    if ((head == NULL) && (tail == NULL))
    {
        cout << "No contact added in favourites !!" << endl;
        return;
    }

    cout << "CONTACTS IN FAVOURITES :" << endl << endl;
    contact* temp = head;  //temporary pointer to traverse the list initialized with head
    do
    {
        if (temp->star == 1)  //if star=1 , it is a favourite contact
        {
            //displaying the details of all favourite contacts
            cout << "CONTACT " << i << " :" << endl;
            cout << "---------" << endl;
            cout << "Name     : " << temp->Name << endl;
            cout << "Number 1 : " << temp->MobNo1 << endl;
            if (temp->MobNo2 == "")
                cout << "Number 2 : Not added " << endl << endl;
            else
                cout << "Number 2 : " << temp->MobNo2 << endl << endl;
            i++;
        }
        temp = temp->next;
    } while (temp != (tail->next));
}

void phoneList::updateContact()
{
    int Choice;
    string name, no1, no2;
    contact* ptr;
    phoneList obj;

    cout << "Enter name of contact which you want to edit : ";
    cin >> name;
    if (obj.searchContact(name, head, tail) == NULL)  //to check if contact exists or not 
    {
        cout << "Name not found !!\n";
        return;
    }

    int flag = 0;
    ptr = head;
    while (ptr->Name != name)
        ptr = ptr->next;
    cout << "Which field you want to update ?" << endl;
    cout << "1. Name\n2. Phone number\n3. Name and number both\n";
    cout << "Select an option : ";
    cin >> Choice;
    switch (Choice)
    {
        //only edit name
    case 1:
        cout << "Enter new name : ";
        cin >> name;
        ptr->Name = name;
        break;
        //only edit mobile number
    case 2:
        cout << "Enter which number do you want to update\n 1 for 1st mobile number and 2 for 2nd mobile number : ";
        cin >> Choice;
        if (Choice == 1)
        {
            cout << "Enter new mobile number : ";
            cin >> no1;
            ptr->MobNo1 = no1;
        }
        else if (Choice == 2)
        {
            cout << "Enter new mobile number : ";
            cin >> no2;
            ptr->MobNo2 = no2;
        }
        else
        {
            cout << "Enter new mobile number : ";
            cin >> no1;
            ptr->MobNo1 = no1;
            cout << "Enter new mobile number : ";
            cin >> no2;
            ptr->MobNo2 = no2;
        }
        break;
        //edit name and number both
    case 3:
        cout << "Enter new name : ";
        cin >> name;
        ptr->Name = name;
        cout << "Enter which number do you want to update\n 1 for 1st mobile number and 2 for 2nd mobile number : ";
        cin >> Choice;
        if (Choice == 1)
        {
            cout << "Enter new mobile number : ";
            cin >> no1;
            ptr->MobNo1 = no1;
        }
        else if (Choice == 2)
        {
            cout << "Enter new mobile number : ";
            cin >> no2;
            ptr->MobNo2 = no2;
        }
        else
        {
            cout << "Enter new mobile number : ";
            cin >> no1;
            ptr->MobNo1 = no1;
            cout << "Enter new mobile number : ";
            cin >> no2;
            ptr->MobNo2 = no2;
        }
        break;
    default:
        cout << "INVALID CHOICE !!" << endl;
        break;
    }
    cout << "\n.......CONTACT UPDATED SUCCESSFULLY !!......." << endl << endl;
}

contact* phoneList::deleteContact(string name)
{
    contact* ptr = head;
    contact* pt = head;

    if (head == NULL && tail == NULL)
    {
        cout << "there is no contact in conact list" << endl;
        return NULL;
    }

    contact* p = searchContact(name, head, tail);
    if (p == NULL)
    {
        cout << "no contact of this name in contactbook" << endl;
        return NULL;
    }

    ptr = head;
    do {
        if (ptr->Name == name)
            break;

        ptr = ptr->next;
    } while (ptr != head);

    if (ptr == head && ptr->next == head)
    {
        head = tail = NULL;
        return ptr;
    }
    else if (ptr == tail)
    {
        tail = tail->prev;
        tail->next = head;
        head->prev = tail;
        return ptr;
    }
    else if (ptr == head && ptr->next != head)
    {
        head = head->next;
        head->prev = tail;
        tail->next = head;
        return ptr;
    }
    else
    {
        ptr->prev->next = ptr->next;
        ptr->next->prev = ptr->prev;
        head->prev = tail;
        tail->next = head;
        return ptr;
    }
}

void phoneList::deleteAllContacts()
{
    //if list is empty
    if ((head == NULL) && (tail == NULL))
    {
        cout << "Phonebook is already empty !!" << endl;
        return;
    }
    else
    {
        while ((head != NULL) && (tail != NULL))
        {
            contact* ptr = head;    //temporary pointer to traverse the list , initialized with starting pointer
            //only one node is present
            if (head == tail)
            {
                head = NULL;
                tail = NULL;
                delete ptr;
            }
            else
            {
                head = head->next;
                delete tail->prev;
                head->prev = tail;
                tail->next = head;
                ptr = head;
            }
        }
        cout << "\n.......ALL CONTACTS CLEARED !! ......." << endl;
    }
}

void phoneList::createBlockList(string name)
{
    phoneList obj;   //object of phoneList class
    //check if contact exists in the phonebook or not
    if (obj.searchContact(name, head, tail) == NULL)
    {
        cout << "NAME NOT FOUND !!\n";
        return;
    }

    contact* ptr = obj.searchContact(name, head, tail);   //pointer to hold the address of searched contact
    contact* temp = new contact(ptr->Name, ptr->MobNo1, ptr->MobNo2, ptr->star);    //creating a new object of class contact
    obj.deleteContact(name);   //deleting this searched node from the phonebook
    //if list is empty
    if (head1 == NULL && tail1 == NULL)
    {
        head1 = tail1 = temp;
        tail1->next = head1;
        head1->prev = tail1;
    }
    //if list is not empty
    else
    {
        temp->prev = tail1;
        tail1->next = temp;
        tail1 = temp;
        tail1->next = head1;
        head1->prev = tail1;
    }
    cout << "........CONTACT UPDATED SUCCESSFULLY !!.......\n";
}

void phoneList::addBackToContactList(string name)
{
    phoneList obj;  //object of phoneList class
    contact* temp = obj.searchContact(name, head1, tail1);  //pointer to hold the address of searched contact
    //check if contact exists or not
    if (temp == NULL)
        cout << "No such contact found in blocklist !!" << endl;
    else
    {
        temp = deleteFromBL(name);
        obj.createContact(temp->Name, temp->MobNo1, temp->MobNo2, temp->star);   //creating new contact of the searched contact in phoneList by using createContact() function
        cout << "........CONTACT ADDED BACK TO PHONEBOOK.......\n";
    }
}

contact* phoneList::deleteFromBL(string name)
{
    contact* ptr = head1;
    contact* pt = head1;

    if (head1 == NULL && tail1 == NULL)
    {
        cout << "there is no contact in conact list" << endl;
        return NULL;
    }

    contact* p = searchContact(name, head1, tail1);
    if (p == NULL)
    {
        cout << "no contact of this name in contactbook" << endl;
        return NULL;
    }

    ptr = head1;
    do {
        if (ptr->Name == name)
            break;

        ptr = ptr->next;
    } while (ptr != head1);

    if (ptr == head1 && ptr->next == head1)
    {
        head1 = tail1 = NULL;
        return ptr;
    }
    else if (ptr == tail)
    {
        tail1 = tail1->prev;
        tail1->next = head1;
        head1->prev = tail1;
        return ptr;
    }
    else if (ptr == head1 && ptr->next != head1)
    {
        head1 = head1->next;
        head1->prev = tail1;
        tail1->next = head1;
        return ptr;
    }
    else
    {
        ptr->prev->next = ptr->next;
        ptr->next->prev = ptr->prev;
        head1->prev = tail1;
        tail1->next = head1;
        return ptr;
    }
}

//driver code
int main()
{
    phoneList obj;   //object of phonebook class
    contact* temp;   //pointer of contact class
    int select = 0;  //for taking input of which task is to be done
    char conti = '\0';   //for taking choice to continue adding contacts in the phonebook
    string Nm;    //to store Name
    string mNo1;  //to store MobNo1
    string mNo2;  //to store MobNo1
    int fav = 0;
    int choice = 0;
    int flag = 0;
    do
    {
        cout << "--------------------------PhoneBook--------------------------" << endl << endl;
        cout << "1. Add a new contact.\n2.Search a contact.\n3.Count total number of contacts.\n4.Display list of all contacts.\n5.Display favourite contacts.\n6.Update/edit a contact.\n7.Add a contact to blocklist.\n8.Display contacts in blocklist.\n9.delete contact from phonebook \n10.Remove a contact from blocklist (i.e. permanently from phonebook).\n11. Clear phonebook.\n12. Remove a contact from blocklist and again move it in phonebook\n\n";
        cout << "Select an option : ";
        cin >> select;
        cout << endl;
        switch (select)
        {
        case 1:
            do
            {
                //if list is empty then take input successfully
                if (head == NULL && tail == NULL)
                {
                    cout << "Enter name : ";
                    cin >> Nm;
                }
                else
                {
                    flag = 0;
                    do
                    {
                        cout << "Enter name : ";
                        cin >> Nm;
                        //to check if inputed name is already present in the phonebook
                        temp = obj.searchContact(Nm, head, tail);
                        //if same name does not exist 
                        if (temp == NULL)
                            flag = 1;
                        //if same name already exists
                        if (flag == 0)
                            cout << "This name already exists." << endl;

                    } while (flag == 0);
                }

                cout << "Enter 1st mobile number : ";
                cin >> mNo1;
                //taking choice from user if he/she wants to add 2nd number
                cout << "\nDo you want to add another mobile number in the same contact ?\nIf yes then enter 1 , else enter 0 : ";
                cin >> choice;

                if (choice == 1)
                {
                    cout << "Enter 2nd mobile number : ";
                    cin >> mNo2;
                    cout << endl;
                }

                else
                    mNo2 = '\0';
                //if fav=1 then it is a favourite contact , else not
                cout << "Do you want to add this contact in your favourite list ?\nIf yes then enter 1 , else enter 0 : ";
                cin >> fav;
                //calling the createContact() function by object of phoneList class
                obj.createContact(Nm, mNo1, mNo2, fav);
                //taking input from user if he/she wants to add another contact in phonebook
                cout << "Do you want to continue adding contacts in your phonebook ?\nIf Yes the enter 'Y' or 'y' , else enter 'N' or 'n': ";
                cin >> conti;
                cout << endl;
            } while (conti == 'Y' || conti == 'y');
            cout << "=============================================================================================================" << endl;
            break;

        case 2:
            cout << "Enter a name you want to search : ";
            cin >> Nm;
            temp = obj.searchContact(Nm, head, tail);
            //check if pointer is null or not null
            if (temp != NULL)
            {
                cout << "Contact found !!" << endl;
                cout << "Name            : " << temp->Name << endl;
                cout << "Mobile Number 1 : " << temp->MobNo1 << endl;
                cout << "Mobile Number 2 : " << temp->MobNo2 << endl;
            }
            else
                cout << "Contact not found !!" << endl;
            cout << "==================================================================================================================" << endl << endl;
            break;

        case 3:
            flag = obj.totalContacts();
            if (flag == -1)
                cout << "Phonebook is empty !!" << endl;
            else
                cout << "Total number of contacts : " << flag << endl;
            cout << "===================================================================================================================" << endl << endl;
            break;

        case 4:
            obj.displayContact(head, tail);
            cout << "====================================================================================================================" << endl << endl;
            break;

        case 5:
            obj.displayFavContacts();
            cout << "====================================================================================================================" << endl << endl;
            break;

        case 6:
            obj.updateContact();
            cout << "=====================================================================================================================" << endl << endl;
            break;

        case 7:
            cout << "Enter name of contact you want to add in the blocklist : ";
            cin >> Nm;
            obj.createBlockList(Nm);
            cout << "=====================================================================================================================" << endl << endl;
            break;

        case 8:
            obj.displayContact(head1, tail1);
            cout << "======================================================================================================================" << endl << endl;
            break;

        case 9:
            cout << "Enter name of contact which you want to delete : ";
            cin >> Nm;
            temp = obj.deleteContact(Nm);
            if (temp != NULL)
                cout << "CONTACT DELETED SUSSFULLY";
            cout << "=====================================================================================================================" << endl << endl;
            break;

        case 10:
            cout << "Enter the contact which you want to remove from block list (i.e. permanently from the phonebook : ";
            cin >> Nm;
            temp = obj.deleteFromBL(Nm);
            if (temp != NULL)
                cout << "CONTACT DELETED SUSSFULLY";
            cout << "=====================================================================================================================" << endl << endl;
            break;

        case 11:
            obj.deleteAllContacts();
            break;

        case 12:
            cout << "Enter the contact which you want to remove from block list and add back in the phonebook : ";
            cin >> Nm;
            obj.addBackToContactList(Nm);
            cout << "=====================================================================================================================" << endl << endl;
            break;

        default:
            cout << "NO MATCH FOUND !!\nPlease enter a valid choice." << endl;
            cout << "======================================================================================================================" << endl << endl;
            break;
        }//switch case

    } while (true);  //do while

}//main
//end of code



