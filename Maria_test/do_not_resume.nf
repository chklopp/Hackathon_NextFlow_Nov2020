#!/bin/env nextflow

//Not working
// how to concatenate a parameter value and a string ?

params.matrixPreprocessedFolder = "$baseDir/results/matrix_processed"
matrixPreprocessedFolder_ch = Channel.fromPath("${params.matrixPreprocessedFolder}/*.pfm")
                                     .map { file -> [ file.name.replace(".pfm",""), file,  "${params.matrixPreprocessedFolder}/" + file.name.replace(".pfm",".score_distrib"), "${params.matrixPreprocessedFolder}/" + file.name.replace(".pfm",".ratio_distrib") ] }
                                     //.view()


//params.matrixFolder = "$baseDir/matrix_firstAnalysis"
params.matrixFolder = "$baseDir/matrix_secondAnalysis"

matrix_ch = Channel.fromPath("${params.matrixFolder}/*.pwm")
                   .map { file -> [ file.name.replace(".pwm",""), file ] }
                 //.view()

// SOLUTION 1 DE GESTION DES MATRICES PREPROCESSEES
/*
Idée, considérer les éléments du channel matrix_ch en un seul élément (collate() ).
Puis retourner une chaîne de caractères qui ne contient que les path des matrices PWM à traîter.
*/
process check_if_preprocessed{
    
    input:
    tuple val(matrix_name), file( pwm) from matrix_ch
    
    output:
    tuple val(matrix_name), file( "*.pwm")into matrices_toProcessed_ch
    
    script:
    """
    if [ ! -e ${params.matrixPreprocessedFolder}"/"$matrix_name".pfm" ]
    then
        echo $matrix_name, $pwm
    fi
    """
}

//matrices_toProcessed_ch.view()

process prepare_matrix {
    
    publishDir "$baseDir/results/matrix_processed", mode: 'link'
    
    input :
    tuple val(matrix_name), file(matrix_file) from matrices_toProcessed_ch
    
    output:
    tuple val(matrix_name), file( "*.pfm"), file("*.score_distrib"), file("*.ratio_distrib") into matrices_processed_ch

    
    script:
    """
    touch ${matrix_name}.pfm
    touch ${matrix_name}.score_distrib 
    touch ${matrix_name}.ratio_distrib
    """
}

//matrices_processed_ch.view()

// SOLUTION 2 DE GESTION DES MATRICES PREPROCESSEES:

/* utiliser une fonction when avec une fonction groovy qui test si le fichier PFM dans le dossier "already preprocessed" n'existe pas déjà.

process prepare_matrix {
    
    publishDir "$baseDir/results/matrix_processed", mode: 'link'
    
    input :
    tuple val(matrix_name), file(matrix_file) from matrices_toProcessed_ch
    
    output:
    tuple val(matrix_name), file( "*.pfm"), file("*.score_distrib"), file("*.ratio_distrib") into matrices_processed_ch

    when:
    File(params.matrixPreprocessedFolder + "/" + ${matrix_name} + ".pfm").exist() == false
    
    script:
    """
    touch ${matrix_name}.pfm
    touch ${matrix_name}.score_distrib 
    touch ${matrix_name}.ratio_distrib
    """
}
*/
// ANALYSE DE COMPARAISON DES VARIANTS
variant_list = ["variant1","var2","var3"]

variant_ch = Channel.fromList(variant_list)

//  ajouter le channel des matrices déjà preprocesser : matrixPreprocessedFolder_ch
compare_ch = variant_ch.combine(matrices_processed_ch)

process do_something {
    
    input:
    tuple val(x), val(matrix_name), file(pfm), file(score), file(ratio) from compare_ch
    
    output:
    env impact into result_ch
    
    script:
    """
    impact=\$( echo compute_impact.pl --variant $x --matrice $pfm --score $score --ratio $ratio)
    """
    
}

result_ch.view()


// but I do not want that matrices M00001 and M00002 are processed again
// add an other channel for previously process matrices ?
// use mix and collect
*/
