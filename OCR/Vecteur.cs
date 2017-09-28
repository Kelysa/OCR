using System;
using System.Collections.Generic;

namespace OCR
{
    //Représente un vecteur de dimension N
    public class Vecteur
    {
        //La liste des composantes du vecteur.
        List<float> components;

        //La dimension du vecteur, c'est-à-dire sa taille,
        //ou, autrement dit, le nombre de composantes qu'il a.
        public int Dimension
        {
            get { return components.Count; }
        }

        //Un indexeur permettant d'avoir accès aux composantes
        //directement en utilisant la syntaxe a[i] et non pas
        //a.components[i]
        public float this[int index]
        {
            get { return components[index]; }
        }

        //Constructeur vide, ne fait que créer une liste de float vide.
        public Vecteur()
        {
            this.components = new List<float>();
        }

        //Constructeur initialisant les composantes selon une liste déjà donnée.
        //(Utilisé lors d'un chargement de donnée par le programme.)
        public Vecteur(List<float> components)
        {
            this.components = components;
        }

        //Retourne une forme 'string' du vecteur.
        //(Utilisée pour sauvegarder le vecteur.)
        public override string ToString()
        {
            string str = components[0].ToString();
            for (int i = 1; i < components.Count; i++)
                str += "," + components[i];
            return str;
        }

        //Ajoute une composante au vecteur.
        //Ce design n'est sans doute pas le meilleur pour un vecteur,
        //puisque, mathématicalement parlant, ils ont une taille fixe,
        //mais du point de vue du programmeur, c'est le moyen le plus
        //facile de faire les choses, le plus comfortable.
        public void Add(float component)
        {
            this.components.Add(component);
        }
    }
}