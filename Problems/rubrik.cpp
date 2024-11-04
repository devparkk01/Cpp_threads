/*

We have a database that supports various levels of backups - full, differential, incremental and log.
Some backups can be dependent on multiple backups.
Dependency information of these backups are,
Full - Does not depend on other backups.
Differential - Depends on Full backup. Back up changes since last data backup(full).
Incremental - Depends on Full/Differential/Incremental. Back up changes since last data(Full) or delta(Differential/Incremental) backup.
Log - Depends on Incremental/Log.
 
Every entry will contain,
  backup_id - backup id of the backup <backup_type><num>
  dependent_id - backup id of the dependent backup <backup_type><num>
  start - starting time of the backup(epoch time)
  end - ending time of the backup(epoch time)
  <backup_type><num>:
example: 
f1 - Full 1
i1 - Incremental 1
d1 - Differential 1
l1 - Log 1
PIT is the point in time to which we want to restore the database. To perform a successful restore to a specific PIT, corresponding chain of dependent backups between Full and PIT should be sequentially restored. This chain of backups is called the recovery chain.
For the same PIT restore, there can be multiple recovery chains. Our goal is to find the recovery chain with the least number of backups.
example: out of 3 possible recovery chains, we need the 3rd one which has least number of backups
f1,i1,i2,i3,l4
f1,i1,l1,l2,l3,l4
f1,d1,i3,l4
Implement the following,
  add_dependency(backup_id, dependent_id, start, end);
    to track the dependency
    backup_id - backup id of the backup <backup_type><num>
    dependent_id - backup id of the dependent backup <backup_type><num>
    start - starting time of the backup for backup_id(epoch time)
    end - ending time of the backup for backup_id(epoch time)
    For Full backups, dependent_id will be zero
  find_recovery_chain(backup_id, pit); // f1
    To find and print the complete chain with the least number of backups
    backup_id is the Full backup
    pit is the epoch time to which we have to restore


10 -> f1
15 -> i1
20 -> d1
25 -> d2

30 -> d3

PIT -> 25

f1 -> i1 -> i2
f1 -> d1

data to be backed up: abcd
10-15 -> abcde
15-20 -> abcdef
10 -> f1 -> abcd
15 -> i1 -> e
20 -> i2 -> f

20 -> d1 -> ef
*/

    // /*backup_id - backup id of the backup <backup_type><num>
    // dependent_id - backup id of the dependent backup <backup_type><num>
    // start - starting time of the backup for backup_id(epoch time)
    // end - ending time of the backup for backup_id(epoch time)
    // For Full backups, dependent_id will be zero*/


#include<iostream>
#include "string"
#include<unordered_map>
#include<queue>


using namespace std; 

class Backup {
  public:
  string backupId; 
  // string dependendId; 
  long start;
  long end; 

  Backup(string backupId, long start, long end): backupId(backupId), start(start), end(end) {}

};


class BackupStructure {
  //  key- > backupid, value-> dependendId 
  unordered_map<string, string> dependencies; 
  unordered_map<string, Backup *> backups; 


  public:
  BackupStructure() {

  }

  void add_dependency(string backup_id, string dependent_id, long  start,long end) {
    auto curBackup = new Backup(backup_id,start, end);
    backups[backup_id] = curBackup;
    dependencies[backup_id] = dependent_id;

  }

  void find_recovery_chain(string backup_id,long pit) {
    // get all the backups at that PIT
    // it stores backups 
    queue<string>q; 

    for(auto &it: backups) {
      if ( it.second->end == pit) {
        q.push(it.first);
      }
    }
    int chain = 0 ; 
    // start BFS search 
    while(!q.empty()) {

      int size = q.size() ;
      while(size --) {
        auto id = q.front(); q.pop(); 
        // if this id is a full backup, return count ;
        if (id[0] == 'f') {
          cout << "chain " << chain << endl; 
          return ; 
        }

        // push the dependency into the queue 
        if ( dependencies[id][0] == 'f') {
          cout << "chain "; 
        }
        q.push(dependencies[id]);
        chain++;
      }
    }

  }

};