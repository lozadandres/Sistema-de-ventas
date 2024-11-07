# Sistema-de-ventas

Este sistema de ventas en C++ es una aplicación que se maneja por consola diseñada para gestionar clientes, productos y facturas, garantizando la organización y control de ventas en un negocio ficticio. Se implementa utilizando los conceptos de programación orientada a objetos (POO), como abstracción, polimorfismo, herencia y composición, para asegurar un código modular y mantenible.

Descripción del Sistema de Ventas
Gestión de Clientes, Productos y Facturas:

El sistema permite registrar y administrar clientes, productos y facturas mediante la implementación de operaciones CRUD (Crear, Leer, Actualizar y Eliminar) específicas para cada entidad.
Cada entidad se representa con su propia clase, utilizando una clase base abstracta que contiene sus métodos abstractos. Estas operaciones se adaptan de manera polimórfica en las clases derivadas para clientes, productos y facturas.
Generación de Facturas:

Al momento de realizar una venta, se genera una factura detallada en un archivo de texto (.txt o .csv), incluyendo:
Nombre de la empresa (ficticia).
Fecha de facturación y número de factura.
Datos completos del cliente.
Detalles de los productos vendidos (cantidad, nombre, precio unitario, subtotal por producto).
Total general de la factura.
Cada factura generada estará lista para impresión y entrega al cliente.
Control de Inventario:

El sistema actualiza automáticamente el inventario al descontar las unidades vendidas de cada producto.
Ofrece reportes de productos agotados y de aquellos con baja rotación, brindando al negocio información útil para la toma de decisiones.
Informes de Ventas:

Permite generar informes de ventas en un rango de fechas, especificando cliente, fecha de factura, número de factura y total, además de la suma total de ventas en el periodo seleccionado. Estos informes se visualizan en la consola y se pueden exportar en archivos de texto (.txt o .csv).
Reportes Adicionales para Análisis:

El sistema también proporciona informes adicionales para obtener información relevante, como tendencias de ventas, análisis de clientes frecuentes y otros indicadores que permitan mejorar la gestión del negocio.
Consideraciones Técnicas
La aplicación está desarrollada en C++ utilizando POO, y cumple con los requisitos de abstracción, polimorfismo, herencia y composición.
Almacena todos los datos en archivos de texto (.csv o .txt), permitiendo su consulta y actualización, incluso después de cerrar la aplicación.
No se pregunta al cliente cuántos productos desea comprar antes de la facturación, siguiendo la rúbrica dada.
