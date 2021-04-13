# procrank
Procrank est un module noyau qui permet de ressortir un ensemble de quatres(04) métriuqes que sont:
- Virtual Set Size (VSS) : Elle représente la mémoire virtuelle allouée à un processus lorsque celle fait une demande d'allocation mémoire.
- Resident Set Size (RSS) : Elle représente la somme des mémoires réellement occupée par le processus sur le système ainsi que celle qu'il partage avec ses compères.
- Unique Set Size (USS) : Quantité de mémoire actuellement occupée par le processus sur le système.
- Proportional Set Size (PSS) : Le rapport de proportioanlité  entre la quantité de  mémoire partagée par les processus  et le nombre de processus les partageant.

# Mise en place du module procrank
Pour reproduire ce travail, il faut:
* Utiliser une version de linux >= 5.8.0
* Définir la structure de données suivante dans le fichier **include/mm.h** puis y déclarer également la fonction **smap_gather_stats** comme suit:
```
struct mem_size_stats {
	unsigned long resident;
	unsigned long shared_clean;
	unsigned long shared_dirty;
	unsigned long private_clean;
	unsigned long private_dirty;
	unsigned long referenced;
	unsigned long anonymous;
	unsigned long lazyfree;
	unsigned long anonymous_thp;
	unsigned long shmem_thp;
	unsigned long file_thp;
	unsigned long swap;
	unsigned long shared_hugetlb;
	unsigned long private_hugetlb;
	u64 pss;
	u64 pss_anon;
	u64 pss_file;
	u64 pss_shmem;
	u64 pss_locked;
	u64 swap_pss;
	bool check_shmem_swap;
};

void smap_gather_stats(struct vm_area_struct *vma, struct mem_size_stats *mss);
```
* Compiler ensuite le noyau [Comment compiler le noyau linux](https://doc.ubuntu-fr.org/tutoriel/compiler_linux)

* Entrer dans le dossier contenant le fichier **procrank.c**
* Le compiler puis l'installer grâce aux commandes suivantes:
	* make
	* make install
* Le charger ensuite dans le noyau grâce à la commande:
	*	```sudo insmod procrank.ko ```
* Pour le décharger, il suffit d'entrer la commande:
	* ```sudo rmmod procrank.ko ```
Une fois le module chargé avec succès, vous pouvez alors consulter ses sorties comme suit:

```cat /proc/procrank```