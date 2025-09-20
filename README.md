# 🧾 Sistema de Gestión para La Panchería

Este es un sistema personalizado desarrollado para un local gastronómico llamado **La Panchería**, orientado a la venta de comida rápida con un menú simple y definido, operando bajo modalidad **take away**.

El sistema fue diseñado para cubrir las necesidades clave del negocio: gestión de productos e ingredientes, ventas y facturación, control de stock, gestión de empleados, clientes y reportes administrativos.

---

## 📌 Introducción

El sistema de gestión a desarrollar es un sistema personalizado para un local gastronómico en particular llamado “La Panchería”.

Este es un local de comida rápida con un menú simple y definido, con alto flujo de demanda. De modalidad take away.

Los objetivos abarcan distintos aspectos como lo son:

- La creación de sus propios ingredientes, productos y recetas (ya que los productos pueden estar compuestos por más de un ingrediente),
- Ventas y facturación,
- El control de stock,
- La atención y la administración general del negocio,

Los cuales se buscan articular para poder tener un flujo dinámico y preciso de las distintas tareas que se realizan día a día en el local.

 
![Menu Inicio](.\LaPancheriaApp/Images/Img_Inicio.png)
---

## 🍔 Productos

El sistema permite:

- Cargar, modificar y eliminar tanto **productos** como **ingredientes**.
- Asociar productos con recetas, permitiendo el control de stock automático y cálculo de costos.
- Ajustar manualmente el stock por auditorías de control, contemplando diferencias mínimas por el tipo de preparación.

 
**Menu Productos**
 
![Descripción](./Images/Img_MenuProductos.png)

**Productos** 
 
![Descripción](./Images/Img_ListadoProductos.png)

 
**Recetas asociadas**
 
![Descripción](./Images/Img_Recetas.png)

 
**Búsqueda de productos por ingredientes**
![Descripción](./Images/Img_Busqueda.png)
---

## 🧾 Ventas

Funcionalidades principales:

- Menú intuitivo para la **toma de pedidos**.
- Filtro por ingredientes para personalizar los productos.
- Selección de distintas formas de pago.
- Generación automática de la **factura**.
- Registro de cliente con DNI. Si es un nuevo cliente, se solicita además nombre y apellido.

**Menu Ventas**
 
![Descripción](./Images/Img_MenuVentas.png)

 
**Elección de productos**

![Descripción](./Images/Img_SeleccionVenta.png) 

 
**Detalle Venta**

 
![Descripción](./Images/Img_DetalleVenta.png) 
---


## 📊 Reportes

Los usuarios con permisos de administrador podrán acceder a un menú exclusivo de reportes para:

- Controlar el estado del negocio.
- Visualizar información clave como:
  - **Balance diario y mensual**,
  - **Productos más vendidos**,
  - **Mejores vendedores**, entre otros.

 
**Menu Reportes**

 
![Descripción](./Images/Img_MenuReportes.png) 

**Ranking productos más vendidos**
 

![Descripción](./Images/Img_RankingMasVendidos.png) 
---

## 👤 Usuarios

El sistema permite:

- Registrar empleados con todos sus datos.
- Asignar uno de los dos tipos
  - `admin`: Acceso completo, incluyendo reportes y gestión.
  - `user`: Acceso limitado solo al menú de ventas.

Cada usuario inicia sesión con su **DNI** y **contraseña**. El sistema permite **3 intentos** de login.

 
**Login intentos fallidos*
 
![Descripción](./Images/Img_MenuLoginFallido.png) 
 
**
---

## 🧑‍🍳 Empleados

Permite:

- Cargar datos personales de los empleados.
- Dar de alta o baja según sea necesario.
- Modificar la información de los registros existentes.

**Menu Empleados
 

![Descripción](./Images/Img_MenuEmpleados.png) 
---

## 👥 Clientes

Durante el proceso de venta se puede:

- Registrar nuevos clientes.
- Modificar datos de clientes existentes.
- O bien, emitir un ticket genérico como **consumidor final** para agilizar la venta.

---

## 💵 Cierre de Caja

Función que permite detallar el total de ventas en efectivo al final de la jornada, facilitando un **cierre de caja preciso**.

---


## 🛠️ Tecnologías utilizadas

- Lenguaje: **C++**
- Paradigma: Programación orientada a objetos
- Persistencia: Archivos binarios
- Compilación: G++ / Dev-C++ / Code::Blocks

---

## 🖥️ Cómo compilar y ejecutar

1. Clonar o descargar el repositorio.
2. Abrir el proyecto en tu IDE preferido 
3. Compilar y ejecutar el programa

## 👥 Integrantes del proyecto

Este proyecto fue desarrollado por estudiantes de la Tecnicatura Universitaria en Programación de la UTN FRGP y defendido en el mes de julio de 2025, como parte del trabajo final de la materia Programación II.

- Bruno Enrique Berti  
- Valentina Gomez Fara  
- Marcos Mazzitelli  
- Julieta Macarena Sanchez  

## 🧑‍🏫 Docentes a cargo

Este proyecto fue realizado bajo la guía de los profesores:

- **Brian Lara**
- **Ángel Simón**

Agradecemos su acompañamiento y dedicación durante el desarrollo del trabajo.

