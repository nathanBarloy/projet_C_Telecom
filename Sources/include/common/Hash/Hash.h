#ifndef HASH_H
#define HASH_H
#ifdef __cplusplus
extern "C"
{
#endif
/*! \brief Permet un hash basique selon l'algorithme Djb2
* \param str Chaine à hasher (ne sera pas modifiée)
* \return Entier representant un hash
*/
unsigned long hashDjb2(unsigned char *str);
/*! \brief Permet un hash basique selon l'algorithme Sdbm
* \param str Chaine à hasher (ne sera pas modifiée)
* \return Entier representant un hash
*/
unsigned long hashSdbm(unsigned char *str);
/*! \brief Permet un hash basique selon l'algorithme LoseLose (best)
* \param str Chaine à hasher (ne sera pas modifiée)
* \return Entier representant un hash
*/
unsigned long hashLoseLose(unsigned char *str);
#ifdef __cplusplus
}
#endif
#endif
