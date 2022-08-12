#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TABLE_SIZE 10

unsigned int keyGenerator(char *key){
    int i=0;
    int slotNumber = 0;
    int value=0;
    for(;i<strlen(key);++i){
        value+=key[i];
    }
    slotNumber = value%TABLE_SIZE;
    return slotNumber;
}

typedef struct ht_t{
    char *name;
    char *job;
    int age;
    struct ht_t *ht;
}ht_t;

typedef struct hashTable{
    ht_t **entry;
}hashTable;

hashTable *createTable(void){
    int i=0;
    hashTable *table =  malloc(sizeof(hashTable)*1);
    table->entry = malloc(sizeof(ht_t)*TABLE_SIZE);
    for(;i<TABLE_SIZE;++i){
        table->entry[i]=NULL;
    }
    return table;}

    ht_t *createEntry(char *name, char *job, int age){
        ht_t *entry = malloc(sizeof(ht_t)*1);
        entry->name = malloc(sizeof(strlen(name)+1)*1);
        entry->job = malloc(sizeof(strlen(job)+1)*1);
        strcpy(entry->name,name);
        strcpy(entry->job,job);
        entry->age=age;
        entry->ht=NULL;
        return entry;
    }

void setTable(hashTable *table, char *name, char *job, int age){
    int slot = keyGenerator(name);
    ht_t *prev;
    ht_t *entry = table->entry[slot];
    if(entry==NULL){
        table->entry[slot] = createEntry(name,job,age);
        return;
    }
    while(entry!=NULL){
        if(strcmp(entry->name,name)==0){
            free(entry->job);
            entry->job = malloc(strlen(job)+1);
            strcpy(entry->job,job);
            return;
        }
        if(entry->ht==NULL){
            ht_t *newEntry = createEntry(name,job,age);
            entry->ht=newEntry;
            return;
        }
        prev=entry;
        entry=prev->ht;
    }
    }


    void ht_dump(hashTable *hashtable){
        int i=0;
    for(i=0; i<TABLE_SIZE; ++i){
        ht_t *entry = hashtable->entry[i];
        if (entry==NULL){
            continue;
        }
        printf("slot[%4d]: \n",i);
        for(;;){
            printf("%s=%s=%d \n", entry->name, entry->job,entry->age);
            if(entry->ht==NULL){
                break;
            }
            entry = entry->ht;
        }
    }
    }
int main()
{
    hashTable *table = createTable();
    setTable(table, "Jesper van de Pavert", "Electrical Engineer", 22);
        setTable(table, "Andre Beethoven", "Electrical Engineer", 22);
    setTable(table, "Pieter van de Beethoven", "Electrical Engineer", 23);
    setTable(table, "Jan van Beethoven", "Electrical Engineer", 22);
    setTable(table, "Koen van drozen", "Electrical Engineer", 52);
    setTable(table, "Ronald van de drozen", "Engineer", 25);
    setTable(table, "Donald drozen", " Engineer", 72);
    setTable(table, "Its Lucassen", "Electrical Engineer", 22);
    setTable(table, "Pyotr van Lucassen", "Electrical Engineer", 12);
    setTable(table, "Rimke van de Lucassen", "Electrical Engineer", 53);
    setTable(table, "Geertruida van de Pavert", "Electrical Engineer", 45);
    setTable(table, "Kees van", "Electrical Engineer", 72);
    setTable(table, "Henk van de", "Electrical Engineer", 35);
    setTable(table, "Frans van de Avond", "Electrical Engineer", 75);
    setTable(table, "Ina van Avond", "Electrical Engineer", 53);
    setTable(table, "Lies de Avond", "Electrical Engineer", 26);
    setTable(table, "Loes van de Nacht", "Electrical Engineer", 47);
    setTable(table, "Sander Nacht", "Electrical Engineer", 28);
    setTable(table, "Marcel Bever", "Electrical Engineer", 36);
    setTable(table, "Ruben van Bever", "Electrical Engineer", 37);
    setTable(table, "Jesper van de Pavert", "CEO", 22);

    ht_dump(table);
    return 0;
}
