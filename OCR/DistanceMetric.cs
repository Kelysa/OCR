using System;
using System.Collections.Generic;

namespace OCR
{
    //L'algorithme de reconnaissance en lui-même.
    public static class DistanceMetric
    {
        //Une liste des distances et des éléments auxquels elles appartiennent.
        //Utilisée pour l'affichage.
        static List<string> distances = new List<string>();

        public static List<string> Distances { get { return distances; } }

        //Fait la reconnaissance à proprement parler depuis l'entrée
        //utilisateur et les images de référence.
        public static string EuclideanRecognition(Vecteur inputVector,
            Dictionary<string, ImageGrid> knowledge)
        {
            distances.Clear();
            //Le nom du caractère le plus proche jusqu'à présent
            string closestGridName = string.Empty;
            //La distance du caractère le plus proche jusqu'à présent
            //A l'origine, la distance est infinie puisqu'on ne compare avec rien.
            float closestDistance = float.PositiveInfinity;


            //Pour chaque image de référence...
            foreach (string itemName in knowledge.Keys)
            {
                //... obtenir le vecteur représentant l'image de référence
                Vecteur itemVector = knowledge[itemName].GetVector();
                //... calculer la distance entre l'entrée utilisateur et
                //    l'image de référence
                float distance = EuclideanDistance(inputVector, itemVector);

                //... si cette distance est la plus petite jusqu'à présent, le noter
                if (distance < closestDistance)
                {
                    closestDistance = distance;
                    closestGridName = itemName;
                }

                distances.Add(itemName + ":" + distance);
            }

            //Retourner le nom du caractère reconnu
            return closestGridName;
        }

        //Calcule la distance entre deux vecteurs.
        //C'est l'implémentation directe de la formule d(a,b) = sqrt(sum( (Ai - Bi)² ))
        //Lance une exception si les vecteurs sont de tailles différentes.
        private static float EuclideanDistance(Vecteur a, Vecteur b)
        {
            if (a.Dimension != b.Dimension)
                throw new ArgumentException("Vectors must be of the same size.");

            float sum = 0f;
            for (int i = 0; i < a.Dimension; i++)
                sum += (a[i] - b[i]) * (a[i] - b[i]);

            return (float)Math.Sqrt(sum);
        }
    }
}