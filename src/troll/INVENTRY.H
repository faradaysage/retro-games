#ifndef INVENTRY_H
#define INVENRTY_H

#define INVENTORY_FILE "invntory.pcx"
#define MAX_INV 3

#define rock_inv    0   
#define gun_inv     1
#define diamond_inv 2

void InitializeInventoryScreen( void );
void ShowInventory( void );
int  GetInventory( int inv );
void SetInventory( int inv, int value );
void CloseInventoryScreen( void );

#endif
